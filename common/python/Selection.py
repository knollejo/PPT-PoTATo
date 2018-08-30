##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Selection.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from Plotable import Plotable

class Selection(Plotable):

    def __init__(self, **options):
        options['labelformat'] = options.get('labelformat', 'with {0}')
        Plotable.__init__(self, **options)
