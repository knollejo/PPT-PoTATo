##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    MissingEtSelection.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action
from Field import Field
from SimpleObservable import SimpleObservable

class MissingEtSelection(Action):

    def __init__(self, **options):
        self.setOption(options, 'cutMissingEt', True)
        self.setOption(options, 'minMissingEt', -1.0)
        self.setOption(options, 'maxMissingEt', -1.0)

    def getAction(self):
        self.action = ROOT.MissingEtSelection(
            self.cutMissingEt, self.minMissingEt, self.maxMissingEt
        )
        return Action.getAction(self)

    @staticmethod
    def Observables():
        return SimpleObservable(
            '*missingEt', fields=Field('missingEt', 'float'),
            nbins=20, xmin=0.0, xmax=200.0, short='met',
            xtitle='E_{T}^{miss} [GeV]'
        )
