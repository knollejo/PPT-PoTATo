##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Condition.py
## Author:  Joscha Knolle
## Date:    2018-05-04
##----------------------------------------------------------------------------##

import ROOT

from Action import Action

class Condition(Action):

    def __init__(self, **options):
        Action.__init__(self, **options)
        self.setOption(options, 'splitEta', None)

    def Or(self, *inputs, **options):
        cond2 = self.__class__(*inputs, **options)
        return OrCondition(self, cond2, name=cond2.name)

    def createCondition(self, init, *inputs):
        if self.splitEta is None:
            return init(*inputs)
        else:
            self.cond1 = init(*[i[0] if type(i) in (list, tuple) else i for i in inputs])
            self.cond2 = init(*[i[1] if type(i) in (list, tuple) else i for i in inputs])
            return ROOT.EtaSplittedCondition(ROOT.Lepton if isinstance(
                self.cond1, ROOT.Condition(ROOT.Lepton)
            ) else ROOT.Jet)(self.splitEta, self.cond1, self.cond2)

class OrCondition(Condition):

    def __init__(self, cond1, cond2, **options):
        Condition.__init__(self, **options)
        self.cond1 = cond1
        self.cond2 = cond2

    def getAction(self):
        cond1 = self.cond1.getAction()
        self.action = ROOT.OrCondition(ROOT.Lepton if isinstance(
            cond1, ROOT.Condition(ROOT.Lepton)) else ROOT.Jet
        )(cond1, self.cond2.getAction())
        return Action.getAction(self)

    def startFile(self, res):
        self.cond1.startFile(res)
        self.cond2.startFile(res)
