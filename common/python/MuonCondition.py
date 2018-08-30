##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    MuonCondition.py
## Author:  Joscha Knolle
## Date:    2018-05-07
##----------------------------------------------------------------------------##

import ROOT

from LeptonCondition import LeptonCondition

class MuonCondition(LeptonCondition):

    def __init__(self, **options):
        LeptonCondition.__init__(self, **options)
        self.setOption(options, 'muons', True)
        self.setOption(options, 'electrons', False)
