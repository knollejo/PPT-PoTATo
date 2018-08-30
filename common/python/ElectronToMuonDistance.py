##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    ElectronToMuonDistance.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class ElectronToMuonDistance(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'mindistance', 0.1)

    def getAction(self):
        self.action = ROOT.ElectronToMuonDistance(self.mindistance)
        return Action.getAction(self)
