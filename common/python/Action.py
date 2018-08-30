##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Action.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import ROOT

class Action:

    def __init__(self, **options):
        self.setOption(options, 'name', None)

    def getAction(self):
        if not hasattr(self, 'action'):
            raise NotImplementedError('Trying to use abstract class Action.')
        if self.name is not None:
            self.renamed = self.action
            self.action = ROOT.RenameAction(self.action, self.name)
        return self.action

    def setOption(self, options, name, default=None):
        setattr(self, name, options.get(name, default))

    def setMinMax(self, options, name, default=-1.0):
        setattr(self, 'min'+name, options.get('min'+name, default))
        setattr(self, 'max'+name, options.get('max'+name, default))

    def startFile(self, res):
        pass
