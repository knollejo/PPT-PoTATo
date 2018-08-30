##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    ZCandidateSelection.py
## Author:  Joscha Knolle
## Date:    2018-05-07
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class ZCandidateSelection(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'cutCandidate', True)
        self.setOption(options, 'maxMassDiff', 10.0)
        self.setOption(options, 'trueZmass', 91.0)

    def getAction(self):
        self.action = ROOT.ZCandidateSelection(
            self.cutCandidate, self.maxMassDiff, self.trueZmass
        )
        return Action.getAction(self)
