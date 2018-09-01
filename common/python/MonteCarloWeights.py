##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    MonteCarloWeights.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class MonteCarloWeights(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)

    def getAction(self):
        self.action = ROOT.MonteCarloWeights()
        return self.action
