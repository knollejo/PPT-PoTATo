##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    LeptonCondition.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Condition import Condition

class LeptonCondition(Condition):

    def __init__(self, **options):
        Condition.__init__(self, **options)
        self.setOption(options, 'muons', None)
        self.setOption(options, 'electrons', None)
        self.setMinMax(options, 'Pt', -1.0)
        self.setMinMax(options, 'Eta', -1.0)
        self.setOption(options, 'requireLooseId', False)
        self.setOption(options, 'invertLooseId', False)
        self.setOption(options, 'requireMediumId', False)
        self.setOption(options, 'invertMediumId', False)
        self.setOption(options, 'requireTightId', False)
        self.setOption(options, 'invertTightId', False)
        self.setMinMax(options, 'PfIso', -1.0)
        self.setMinMax(options, 'MiniIso', -1.0)

    def getAction(self):
        if self.muons and not self.electrons:
            cutelec, cutmuon = False, True
        elif self.electrons and not self.muons:
            cutelec, cutmuon = True, False
        else:
            cutelec, cutmuon = True, True
        self.action = self.createCondition(
            ROOT.LeptonCondition,
            self.minPt, self.maxPt, self.minEta, self.maxEta,
            cutelec, cutmuon, self.requireLooseId, self.invertLooseId,
            self.requireMediumId, self.invertMediumId, self.requireTightId, self.invertTightId, 
            self.minPfIso, self.maxPfIso,
            self.minMiniIso, self.maxMiniIso
        )
        return Condition.getAction(self)
