##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    JetCondition.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Condition import Condition

class JetCondition(Condition):

    def __init__(self, **options):
        Condition.__init__(self, **options)
        self.setMinMax(options, 'Pt', -1.0)
        self.setMinMax(options, 'Eta', -1.0)
        self.setOption(options, 'cutPileup', False)
        self.setOption(options, 'invertPileup', False)
        self.setOption(options, 'pileupWP', -1)
        self.setOption(options, 'btagWP', -1.0)
        self.setMinMax(options, 'Btag', -1.0)

    def getAction(self):
        self.action = self.createCondition(
            ROOT.JetCondition,
            self.minPt, self.maxPt, self.minEta, self.maxEta,
            self.cutPileup, self.invertPileup, self.pileupWP, self.btagWP,
            self.minBtag, self.maxBtag
        )
        return Condition.getAction(self)
