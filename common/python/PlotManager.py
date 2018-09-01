##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    PlotManager.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import itertools
from math import log10

import ROOT

from Category import Category
from EventStreams import EventStreams
from Observable import Observable
from PlotCombiner import PlotCombiner
from PostProcessor import PostProcessor
from Selection import Selection

class PlotManager(PostProcessor):

    def __init__(self, *inputs, **options):
        self.observables = []
        self.categories = []
        self.selections = []
        self.combiners = []
        PostProcessor.__init__(self, *inputs, **options)
        self.short = options.get('short', None)
        self.luminosity = options.get('luminosity', None)

    def add(self, *inputs):
        inputs = PostProcessor.add(self, *inputs)
        failed = []
        for obj in inputs:
            if isinstance(obj, Observable):
                self.observables.append(obj)
            elif isinstance(obj, Category):
                self.categories.append(obj)
            elif isinstance(obj, Selection):
                self.selections.append(obj)
            elif isinstance(obj, PlotCombiner):
                self.combiners.append(obj)
        return failed

    def generate(self):
        PostProcessor.generate(self)

        with open('common/src/PlotManager.cpp') as f:
            code = f.read()
        code = dict(map(lambda key: (
            key.lower(),
            code.split('/*$#{BEGIN_'+key+'}#$*/')[1] \
                .split('/*$#{END_'+key+'}#$*/')[0]
        ), (
            'INCLUDES', 'DEFINITIONS', 'INITIALIZATIONS', 'CONSTRUCTIONS',
            'ACTION', 'OUTPUTS',
        )))
        self.C_includes += code['includes'].split('\n')
        self.C_definitions.append(code['definitions'])
        self.C_initializations.append(code['initializations'])
        self.C_constructions.append(code['constructions'])
        self.C_action.append(code['action'])
        self.C_outputs.append(code['outputs'])

        for cmb in self.combiners:
            map(lambda c: cmb.registerCategory(
                c.short, c.Label(latex=True)
            ), self.categories)
            map(lambda s: cmb.registerSelection(
                s.short, s.Label(latex=True)
            ), self.selections)

        nStreams = len(self.eventstreams)
        nPlot = 0
        for sel in self.selections:
            self.C_action.append('if({}) {{'.format(sel.Condition()))
            self.C_action.append('selweight = weight*({});'.format(sel.Weight()))
            for cat in self.categories:
                self.C_action.append('if({}) {{'.format(cat.Condition()))
                self.C_action.append('catweight = selweight*({});'.format(cat.Weight()))
                ytitle = ' '.join(
                    filter(None, (cat.Label(), 'Ereignisse', sel.Label()))
                )
                for obs in self.observables:
                    if obs.Skip(cat.short, sel.short):
                        continue
                    name = '_'.join(filter(None, map(lambda x: x.short, (
                        self, obs, sel, cat
                    ))))
                    for cmb in self.combiners:
                        cmb.addPlot(name, sel.short, cat.short)
                    # Add histograms to constructor
                    histnames = ['plot{0}_hist{1}_{2}'.format(
                        nPlot, i, name
                    ) for i in range(nStreams)]
                    self.C_constructions += [
                        obs.Hist(hname) for hname in histnames
                    ]+[
                        'TH1** plot{0}_hists_{1} = new TH1*[{2}];'
                        .format(nPlot, name, nStreams)
                    ]+[
                        'plot{0}_hists_{1}[{2}] = {3};'
                        .format(nPlot, name, i, hname)
                        for i, hname in enumerate(histnames)
                    ]+[
                        '_plots[{0}].hists = plot{0}_hists_{1};'.format(nPlot, name),
                        '_plots[{0}].name = "{1}";'.format(nPlot, name),
                        '_plots[{0}].addOverflow = {1};'.format(
                            nPlot, self.C_bool(not obs.ignoreOverflow)
                        ),
                        '_plots[{0}].xtitle = "{1}";'.format(nPlot, '' if obs.xtitle is None else obs.xtitle),
                        '_plots[{0}].ytitle = "{1}";'.format(nPlot, ytitle),
                        '_plots[{0}].largelabels = {1};'.format(
                            nPlot, self.C_bool(obs.largelabels)
                        ),
                        '_plots[{0}].xdivisions = {1};'.format(
                            nPlot,
                            obs.xdivisions if obs.xdivisions is not None else 0
                        ),
                    ]
                    # Fill histograms in fill function
                    self.C_action.append('if({}) {{'.format(obs.Condition()))
                    self.C_action.append('evweight = catweight*({});'.format(obs.Weight()))
                    fill = obs.Draw('_plots[{0}].hists[nStream]'.format(nPlot))
                    if type(fill) in (list, tuple):
                        self.C_action += fill
                    else:
                        self.C_action.append(fill)
                    self.C_action.append('}')
                    nPlot += 1
                self.C_action.append('}')
            self.C_action.append('}')

        for nStream, stream in enumerate(self.eventstreams):
            self.C_constructions += stream.Style(nStream)
            self.C_constructions.append('_forStack[{0}] = {1};'.format(
                nStream, self.C_bool(stream.stacked)
            ))

        self.addIncludes(self.selections, self.categories, self.observables)
        self.addFields(self.selections, self.categories, self.observables)
        self.addDefinitions(self.selections, self.categories, self.observables)

        self.replacements += [
            ('NPLOTS', str(nPlot)),
            ('LUMINOSITY', '"{}"'.format(self.luminosity if self.luminosity else '')),
        ]

    def finalize(self):
        PostProcessor.finalize(self)
        for cmb in self.combiners:
            cmb.write(name=self.short)
