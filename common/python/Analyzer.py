##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Analyzer.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

from Action import Action
from Mode import Mode
from Sample import Sample

class Analyzer:

    def __init__(self):
        self.actions = []
        self.outputFile = None

    def writeOutput(self, filename):
        self.outputFile = filename

    def initialize(self):
        self.analyzer = ROOT.Analyzer()
        for action in self.actions:
            self.analyzer.registerAction(action.getAction())
        if self.outputFile is not None:
            self.analyzer.setOutput(self.outputFile)
        self.analyzer.initialize()

    def process(
        self, tree, mode=None, sample=None, xsec=-1, nevents=-1,
        res=None, boundaries=None
    ):
        if mode is None:
            mode = Mode.None
        if sample is None:
            sample = Sample.None
        if boundaries is None:
            boundaries = (-1, -1)
        if res is not None:
            for action in self.actions:
                action.startFile(res)
        self.analyzer.processTree(
            tree, mode, sample, xsec, nevents, boundaries[0], boundaries[1]
        )

    def finalize(self):
        self.analyzer.finalize()

    def register(self, *actions):
        for action in actions:
            self.actions.append(action)

    def getResult(self):
        return self.analyzer.getResult()
