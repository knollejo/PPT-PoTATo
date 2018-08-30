##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    EventStreams.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import itertools
import math
import os

import ROOT

from Field import Field
from Mode import Mode
from Processible import Processible
from Sample import Sample

class EventStream(Processible):

    def __init__(self, *modesample, **options):
        Processible.__init__(self, **options)
        self.setModeSample(*modesample)
        self.setOption(options, 'markercolor', 1)
        self.setOption(options, 'markerstyle', 8)
        self.setOption(options, 'linecolor', 1)
        self.setOption(options, 'linestyle', 1)
        self.setOption(options, 'fillcolor', 0)
        self.setOption(options, 'fillstyle', 0)
        self.setOption(options, 'stacked', False)
        self.setOption(options, 'weighted', False)
        self.setOption(options, 'luminosity', 0.0)
        self.setOption(options, 'userweight')

    def setModeSample(self, *modesample):
        self.modesample = []
        self.addModeSample(*modesample)

    def addModeSample(self, *modesample):
        for mode, sample in zip(*[iter(modesample)]*2):
            modes = Mode.part(mode)
            samples = Sample.part(sample)
            self.modesample += list(itertools.product(modes, samples))

    def Condition(self):
        return reduce(lambda c1, c2: '{0} || {1}'.format(c1, c2), map(
            lambda (m, s): '(*modeid=={0} && *sampleid=={1})'.format(m, s),
            self.modesample
        ))

    def Weight(self):
        weights = ['*weight']
        if self.weighted:
            weights.append('*lumifactor')
            weights.append(self.luminosity)
        if self.userweight is not None:
            weights.append(self.userweight)
        return reduce(lambda w1, w2: '({0})*({1})'.format(w1, w2), weights, 1.0)

    def Fields(self):
        flds = Processible.Fields(self).union([
            Field('modeid', 'int'), Field('sampleid', 'int'),
            Field('weight', 'float')
        ])
        if self.weighted:
            flds = flds.union([Field('lumifactor', 'float')])
        return flds

    def Style(self, nstream):
        return map(lambda s: s.format(
            nstream, self.markercolor, self.markerstyle, self.linecolor,
            self.linestyle, self.fillcolor, self.fillstyle
        ), [
            '_stylecontainers[{0}].markercolor = {1};',
            '_stylecontainers[{0}].markerstyle = {2};',
            '_stylecontainers[{0}].linecolor = {3};',
            '_stylecontainers[{0}].linestyle = {4};',
            '_stylecontainers[{0}].fillcolor = {5};',
            '_stylecontainers[{0}].fillstyle = {6};',
        ])

    def Open(self):
        files = []
        names = map(lambda ms: '_'.join(filter(None, (
            self.name, Mode.getName(ms[0]), Sample.getName(ms[1])
        ))), self.modesample)
        for f in os.listdir('output'):
            if not f.endswith('.root'):
                continue
            if filter(lambda n: f.startswith(n), names):
                files.append('output/'+f)
        if len(files)>1:
            self._close = 'delete _chain;'
            return '\n'.join(['', '_chain = new TChain("result");']+[
                '_chain->Add("{0}");'.format(f) for f in files
            ]+['return _chain;', ''])
        elif len(files)==1:
            self._close = '_file->Close();'
            return '\n'.join(['',
                '_file = TFile::Open("{0}");'.format(files[0]),
                'TTree* tree = (TTree*)_file->Get("result");',
                'return tree;'
            ''])
        else:
            raise IndexError('Couldn\'t find files for '+self.title)

    def Close(self):
        return self._close

class EventStreamsClass:

    def isinstance(self, obj):
        return isinstance(obj, EventStream)

    def new(self, *modesample, **options):
        return EventStream(*modesample, **options)

    def Data(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.Data, Sample.Data]
        opt = {'name': 'Data'}
        opt.update(options)
        return EventStream(*modesample, **opt)

    def MonteCarlo(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.MonteCarlo, Sample.MonteCarlo]
        opt = {
            'name': 'MC',
            'stacked': True,
            'markerstyle': 0,
            'fillstyle': 1001,
            'fillcolor': 2,
            'weighted': True,
        }
        opt.update(options)
        return EventStream(*modesample, **opt)

    def Data2016(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.Data, Sample.Run2016]
        return self.Data(*modesample, **options)

    def Data2017(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.Data, Sample.Run2017]
        return self.Data(*modesample, **options)

    def MonteCarlo2016(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.MonteCarlo, Sample.MC2016]
        return self.MonteCarlo(*modesample, **options)

    def MonteCarlo2017(self, *modesample, **options):
        if len(modesample)<2:
            modesample = [Mode.MonteCarlo, Sample.MC2017]
        return self.MonteCarlo(*modesample, **options)

EventStreams = EventStreamsClass()
