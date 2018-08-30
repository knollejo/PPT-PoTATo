##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    __init__.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import importlib
import os

__all__ = []
for name in os.listdir(os.path.dirname(os.path.abspath(__file__))):
    if name.endswith('.py') and not name.startswith('_'):
        mod = name[:-3]
        globals()[mod] = getattr(importlib.import_module('common.python.'+mod), mod)
        __all__.append(mod)
