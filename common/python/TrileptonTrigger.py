##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: trileptonic
## File:    TrileptonTrigger.py
## Author:  Joscha Knolle
## Date:    2018-05-07
##----------------------------------------------------------------------------##

import ROOT

from Action import Action
from Mode import Mode
from Sample import Sample

class TrileptonTrigger(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'runOnDoubleMuon', True)
        self.setOption(options, 'runOnDoubleElectron', True)
        self.setOption(options, 'runOnElectronMuon', True)
        self.setOption(options, 'runOnSingleMuon', True)
        self.setOption(options, 'runOnSingleElectron', True)
        self.setOption(options, 'cutMonteCarlo', True)

    def getAction(self):
        modes = (0
            + Mode.DoubleMuon * self.runOnDoubleMuon
            + Mode.DoubleElectron * self.runOnDoubleElectron
            + Mode.ElectronMuon * self.runOnElectronMuon
            + Mode.SingleMuon * self.runOnSingleMuon
            + Mode.SingleElectron * self.runOnSingleElectron
            + Mode.MonteCarlo
        )
        self.action = ROOT.TrileptonTrigger(self.cutMonteCarlo)
        self.action.setDatasets(modes)
        return Action.getAction(self)
