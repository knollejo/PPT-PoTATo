##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Plotable.py
## Author:  Joscha Knolle
## Date:    2018-05-14
##----------------------------------------------------------------------------##

from Processible import Processible

class Plotable(Processible):

    def __init__(self, **options):
        Processible.__init__(self, **options)
        self.setOption(options, 'label')
        self.setOption(options, 'latexlabel', self.label)
        self.setOption(options, 'short')
        self.setOption(options, 'labelformat', '{0}')
        self.setOption(options, 'condition')
        self.setOption(options, 'weight')

    def Label(self, latex=False):
        if latex and self.latexlabel:
            return self.labelformat.format(self.latexlabel)
        elif not latex and self.label:
            return self.labelformat.format(self.label)
        else:
            return None

    def Condition(self):
        if self.condition is None:
            return 'true'
        elif not isinstance(self.condition, basestring):
            return 'true' if self.condition else 'false'
        else:
            return self.condition

    def Weight(self):
        if self.weight is None:
            return '1.0'
        elif not isinstance(self.weight, basestring):
            return '{0}'.format(self.weight)
        else:
            return self.weight
