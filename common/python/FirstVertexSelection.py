##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    FirstVertexSelection.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class FirstVertexSelection(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'cutFirstVertices', True)

    def getAction(self):
        self.action = ROOT.FirstVertexSelection(self.cutFirstVertices)
        return Action.getAction(self)
