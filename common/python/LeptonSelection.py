##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    LeptonSelection.py
## Author:  Joscha Knolle
## Date:    2018-05-07
##----------------------------------------------------------------------------##

from array import array

import ROOT

from Action import Action

class LeptonSelection(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'muons', None)
        self.setOption(options, 'electrons', None)
        self.setOption(options, 'cutNumber', False)
        self.setOption(options, 'storeNumber', False)
        self.setOption(options, 'storePdgId', False)
        self.setOption(options, 'storePt', False)
        self.setOption(options, 'storeEta', False)
        self.setOption(options, 'storePhi', False)
        self.setOption(options, 'storeKinematics', False)
        self.setOption(options, 'storeRelIso', False)
        self.setOption(options, 'storeMiniIso', False)
        self.setMinMax(options, 'Number', -1)
        self.setOption(options, 'minPt', -1.0)

    def getAction(self):
        if self.muons and not self.electrons:
            onlyelec, onlymuon = True, False
        elif self.electrons and not self.muons:
            onlyelec, onlymuon = False, True
        else:
            onlyelec, onlymuon = False, False
        if type(self.minPt) in (list, tuple):
            nminleppt = len(self.minPt)
            minleppt = array('f', self.minPt[:])
        elif self.minPt>0:
            nminleppt = 10
            minleppt = array('f', [self.minPt]*10)
        else:
            nminleppt = -1
            minleppt = array('f', [0.0])
        self.action = ROOT.LeptonSelection(
            self.cutNumber, onlymuon, onlyelec,
            self.storeNumber or self.storeKinematics or self.storeEverything,
            self.storePdgId or self.storeKinematics or self.storeEverything,
            self.storePt or self.storeKinematics or self.storeEverything,
            self.storeEta or self.storeKinematics or self.storeEverything,
            self.storePhi or self.storeKinematics or self.storeEverything,
            self.storeRelIso or self.storeEverything,
            self.storeMiniIso or self.storeEverything,
            self.minNumber, self.maxNumber, nminleppt, minleppt
        )
        return Action.getAction(self)
