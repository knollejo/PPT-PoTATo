##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    SimpleObservable.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from Observable import Observable

class SimpleObservable(Observable):

    with open('common/src/SimpleObservable.cpp') as f:
        _code = f.read()
        C_removenegative = _code.split('/*$#{BEGIN_REMOVENEGATIVE}#$*/')[1] \
                                .split('/*$#{END_REMOVENEGATIVE}#$*/')[0]
        C_addoverflow = _code.split('/*$#{BEGIN_ADDOVERFLOW}#$*/')[1] \
                             .split('/*$#{END_ADDOVERFLOW}#$*/')[0]
        C_setstyle = _code.split('/*$#{BEGIN_SETSTYLE}#$*/')[1] \
                          .split('/*$#{END_SETSTYLE}#$*/')[0]

    def __init__(self, field, **options):
        Observable.__init__(self, **options)
        self.field = field

    def Draw(self, name):
        return '{0}->Fill({1}, evweight);'.format(name, self.field)

    def Style(self):
        style = []
        if self.ignoreOverflow:
            style += self.C_ignoreOverflow
        if self.removeNegative:
            style += self.C_removenegative
        style += self.C_setstyle
        return style
