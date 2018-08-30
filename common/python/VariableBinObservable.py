##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    VariableBinObservable.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from SimpleObservable import SimpleObservable

class VariableBinObservable(SimpleObservable):

    def __init__(self, field, bins, **options):
        SimpleObservable.__init__(self, field, **options)
        self.bins = bins

    def Hist(self, name):
        self.nbins = len(self.bins)-1
        self.xmin = self.bins[0]
        self.xmax = self.bins[-1]
        return '\n'.join((
            'float {0}_binning[{1}] = {{{2}}};'.format(
                name, self.nbins+1, ','.join(map(str, self.bins))
            ),
            'TH1* {0} = new TH1F("{0}", "", {1}, {0}_binning);'.format(
                name, self.nbins
            ),
            '{0}->Sumw2();'.format(name),
            '{0}->SetBinErrorOption(TH1::EBinErrorOpt::kPoisson);'.format(name),
        ))
