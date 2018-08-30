##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    InputFiles.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from Mode import Mode
from Sample import Sample

class InputFiles:

    def __init__(self, *inputs, **options):
        self.files = []
        self.add(*inputs, **options)

    def add(self, *inputs, **options):
        mode = options.get('mode', Mode.None)
        sample = options.get('sample', Sample.None)
        xsec = options.get('xsec', -1.0)
        nevents = options.get('nevents', -1)
        for obj in inputs:
            if isinstance(obj, InputFiles):
                self.files = self.files + obj.files
            else:
                self.files.append((obj, mode, sample, xsec, nevents))

    def __add__(self, other):
        return InputFiles(self, other)

    def __radd__(self, other):
        if other:
            return self.__add__(other)
        else:
            return self

    def iterate(self, mode=None, sample=None):
        if mode is None:
            isMode = lambda m: True
        else:
            isMode = (lambda m1: lambda m2: (m1&m2)!=0)(mode)
        if sample is None:
            isSample = lambda s: True
        else:
            isSample = (lambda s1: lambda s2: (s1&s2)!=0)(sample)
        for f, m, s, x, n in self.files:
            if isMode(m) and isSample(s):
                yield (f, m, s, x, n)


class InputFileCollection:
    pass
