##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    JetToLeptonDistance.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class JetToLeptonDistance(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'mindistance', 0.4)

    def getAction(self):
        self.action = ROOT.JetToLeptonDistance(self.mindistance)
        return Action.getAction(self)
