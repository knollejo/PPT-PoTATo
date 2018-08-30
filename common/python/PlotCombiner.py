##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    PlotCombiner.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from datetime import datetime
from itertools import imap, product
import os
from subprocess import call

Format = lambda s: lambda x: s.format(filter(None, x))
Join = lambda s: lambda x: s.join(filter(None, x))
Tuple = lambda n: lambda x: zip(*[iter(x+[None]*(n-1))]*n)

class PlotCombiner:

    def __init__(self, **options):
        self.name = options.get('name', 'summary')
        self.graph = options.get(
            'graph', '\\includegraphics[width=0.47\\textwidth]{{{{{0}}}}}'
        )
        self.interGraph = options.get('interGraph', '\\hfill')
        self.interLine = options.get('interLine', '\\\\[2em]\n')
        self.interPage = options.get('interPage', '\\newpage\n')
        self.part = options.get('part', '\n'.join((
            '\\clearpage',
            '\\lhead{{{1}}}',
            '\\refstepcounter{{section}}',
            '\\pdfbookmark{{{1}}}{{bookmark\\thesection}}',
            '{0}'
        )))
        self.document = options.get('document', '\n'.join((
            '\\documentclass[10pt,a4paper,notitlepage,oneside]{{article}}',
            '\\usepackage[left=1cm,right=1cm,top=2.5cm,bottom=2cm]{{geometry}}',
            '\\usepackage{{fancyhdr}}',
            '\\pagestyle{{fancy}}',
            '\\usepackage[bookmarks=true]{{hyperref}}',
            '\\lhead{{}}',
            '\\chead{{}}',
            '\\rhead{{{1}}}',
            '\\lfoot{{}}',
            '\\cfoot{{\\thepage}}',
            '\\rfoot{{}}',
            '\\usepackage{{graphicx}}',
            '\\graphicspath{{{{plots/}}}}',
            '\\setlength\\parindent{{0pt}}',
            '\\begin{{document}}',
            '{0}',
            '\\end{{document}}',
        )))
        self.pdflatex = options.get(
            'pdflatex', 'pdflatex -interaction=batchmode {0}.tex >/dev/null'
        )
        self.dateformat = options.get('dateformat', '%d.%m.%Y, %H:%M:%S')

        self.sortby = options.get('sortby', '')
        if 'category'.startswith(self.sortby.lower()):
            self.plots = {}
            self.categories = []
            self.catlabels = {}
            self.selections = None
            self.addPlot = lambda name, sel, cat: self.plots[cat].append(name)
            self.iterPlots = lambda: imap(
                lambda cat: (cat, self.catlabels[cat], self.plots[cat]),
                self.categories
            )
        elif 'selection'.startswith(self.sortby.lower()):
            self.plots = {}
            self.categories = None
            self.selections = []
            self.sellabels = {}
            self.addPlot = lambda name, sel, cat: self.plots[sel].append(name)
            self.iterPlots = lambda: imap(
                lambda sel: (sel, self.sellabels[sel], self.plots[sel]),
                self.selections
            )
        elif 'both'.startswith(self.sortby.lower()):
            self.plots = {}
            self.categories = []
            self.catlabels = {}
            self.selections = []
            self.sellabels = {}
            self.addPlot = lambda name, sel, cat: self.plots[cat][sel].append(name)
            self.iterPlots = lambda: imap(lambda (sel, cat): (
                Join('_')((sel, cat)),
                Join(', ')((self.catlabels[cat], self.sellabels[sel])),
                self.plots[cat][sel]
            ), product(self.selections, self.categories))
        else:
            self.plots = []
            self.categories = None
            self.selections = None
            self.addPlot = lambda name, sel, cat: self.plots.append(name)
            self.iterPlots = lambda: [('', '', self.plots)]

    def registerCategory(self, short, label):
        if self.categories is not None:
            self.categories.append(short)
            self.catlabels[short] = label
            self.plots[short] = [] if self.selections is None else {
                sel: [] for sel in self.selections
            }

    def registerSelection(self, short, label):
        if self.selections is not None:
            self.selections.append(short)
            self.sellabels[short] = label
            if self.categories is None:
                self.plots[short] = []
            else:
                map(lambda cat: cat.update({short: []}), self.plots.itervalues())

    def Part(self, *plots, **options):
        title = options.get('title', '')
        return (
            # join all pages to form a part
            self.part.format(Join(self.interPage)(
                # join 4 lines to form a page
                map(Join(self.interLine), Tuple(3)(
                    # join 2 plots to form a line
                    map(Join(self.interGraph), Tuple(2)(
                        # draw plot
                        map(Format(self.graph), plots))
                    )
                ))
            ), title)
        )

    def Document(self, *parts):
        return self.document.format(
            Join('\n')(parts), datetime.now().strftime(self.dateformat)
        )

    def latexFile(self, name, content):
        temp = '{0}_temp'.format(name)
        with open(temp+'.tex', 'w') as f:
            f.write(content)
        call(self.pdflatex.format(temp), shell=True)
        call(self.pdflatex.format(temp), shell=True)
        os.rename(temp+'.pdf', 'plots/{0}.pdf'.format(name))
        for f in os.listdir('.'):
            if f.startswith(temp):
                os.remove(f)
        print 'Info in <pdflatex>: pdf file plots/{0}.pdf has been created' \
              .format(name)

    def write(self, **options):
        parts = []
        for section, title, plots in self.iterPlots():
            name = Join('_')((options.get('name', 'plots'), self.name, section))
            parts.append(self.Part(*plots, title=title))
            self.latexFile(name, self.Document(parts[-1]))
        if self.selections is not None or self.categories is not None:
            name = Join('_')((options.get('name', 'plots'), self.name))
            self.latexFile(name, self.Document(*parts))
