##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    JetSelection.py
## Author:  Joscha Knolle
## Date:    2018-05-07
##----------------------------------------------------------------------------##

from array import array

import ROOT

from Action import Action

class JetSelection(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'cutNumber', False)
        self.setOption(options, 'cutNumberBtags', False)
        self.setOption(options, 'storeNumber', False)
        self.setOption(options, 'storePt', False)
        self.setOption(options, 'storeEta', False)
        self.setOption(options, 'storePhi', False)
        self.setOption(options, 'storeKinematics', False)
        self.setOption(options, 'storeNumberBtags', False)
        self.setOption(options, 'storeBtagDisc', False)
        self.setOption(options, 'storeBtags', False)
        self.setMinMax(options, 'Number', -1)
        self.setMinMax(options, 'NumberBtags', -1)
        self.setOption(options, 'minPt', -1.0)

    def getAction(self):
        if type(self.minPt) in (list, tuple):
            nminjetpt = len(self.minPt)
            minjetpt = array('f', self.minPt[:])
        elif self.minPt>0:
            nminjetpt = 10
            minjetpt = array('f', [self.minPt]*10)
        else:
            nminjetpt = -1
            minjetpt = array('f', [0.0])
        self.action = ROOT.JetSelection(
            self.cutNumber, self.cutNumberBtags,
            self.storeNumber or self.storeKinematics,
            self.storePt or self.storeKinematics,
            self.storeEta or self.storeKinematics,
            self.storePhi or self.storeKinematics,
            self.storeNumberBtags or self.storeBtags,
            self.storeBtagDisc or self.storeBtags,
            self.minNumber, self.maxNumber, self.minNumberBtags,
            self.maxNumberBtags, nminjetpt, minjetpt
        )
        return Action.getAction(self)
