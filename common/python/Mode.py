##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Mode.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import itertools
import math

import ROOT

class ModeClass:

    def __init__(self):
        self.names = {}
        for key in ROOT.Mode.__dict__:
            if not key.startswith('_'):
                mode = getattr(ROOT.Mode, key)
                setattr(self, key, mode)
                self.names[mode] = key

    def getName(self, mode):
        return self.names.get(mode, 'None')

    def part(self, mode):
        if mode&(mode-1):
            modes = []
            for i in range(int(math.log(mode, 2))):
                if mode&(2**(i+1)):
                    modes.append(2**(i+1))
        else:
            modes = [mode]
        return modes

Mode = ModeClass()
