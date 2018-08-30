##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Observable.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from Plotable import Plotable

class Observable(Plotable):

    def __init__(self, **options):
        options['short'] = options.get('short', 'obs')
        Plotable.__init__(self, **options)
        self.nbins = options.get('nbins', 30)
        self.xmin = options.get('xmin', 0)
        self.xmax = options.get('xmax', 100)
        self.xtitle = options.get('xtitle', None)
        self.ignoreOverflow = options.get('ignoreOverflow', False)
        self.removeNegative = options.get('removeNegative', True)
        self.skipcats = options.get('skipcats', None)
        self.onlycats = options.get('onlycats', None)
        self.skipsels = options.get('skipsels', None)
        self.onlysels = options.get('onlysels', None)
        self.largelabels = options.get('largelabels', False)
        self.xdivisions = options.get('ndivisions', None)

    def Skip(self, category, selection):
        return (
            (self.skipcats is not None and category in self.skipcats) or
            (self.skipsels is not None and selection in self.skipsels) or
            (self.onlycats is not None and category not in self.onlycats) or
            (self.onlysels is not None and selection not in self.onlysels)
        )

    def Hist(self, name):
        return '\n'.join((
            'TH1* {3} = new TH1F("{3}", "", {0}, {1}, {2});',
            '{3}->Sumw2();', '{3}->SetBinErrorOption(TH1::EBinErrorOpt::kPoisson);'
        )).format(self.nbins, self.xmin, self.xmax, name)

    def Draw(self):
        raise RuntimeError('Called abstract function "Draw"!')

    def Style(self):
        return ''
