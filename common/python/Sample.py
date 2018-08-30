##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Sample.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import itertools
import math

import ROOT

class SampleClass:

    def __init__(self):
        self.names = {}
        for key in ROOT.Sample.__dict__:
            if not key.startswith('_'):
                sample = getattr(ROOT.Sample, key)
                setattr(self, key, sample)
                self.names[sample] = key

    def getName(self, sample):
        return self.names.get(sample, 'None')

    def part(self, sample):
        if sample&(sample-1):
            samples = []
            for i in range(int(math.log(sample, 2))):
                if sample&(2**(i+1)):
                    samples.append(2**(i+1))
        else:
            samples = [sample]
        return samples

Sample = SampleClass()
