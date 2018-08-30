##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Processible.py
## Author:  Joscha Knolle
## Date:    2018-05-14
##----------------------------------------------------------------------------##

class Processible:

    def __init__(self, **options):
        self.setOption(options, 'name')
        self.setOption(options, 'title')
        self.setOption(options, 'fields')
        self.setOption(options, 'includes')

    def setOption(self, options, name, default=None):
        setattr(self, name, options.get(name, default))

    def Fields(self):
        if self.fields is None:
            return set()
        elif isinstance(self.fields, (list, tuple)):
            return set(self.fields)
        elif isinstance(self.fields, set):
            return self.fields
        else:
            return set((self.fields,))

    def Includes(self):
        if self.includes is None:
            return set()
        elif isinstance(self.includes, (list, tuple)):
            return set(self.includes)
        elif isinstance(self.includes, set):
            return self.includes
        else:
            return set((self.includes,))

    def Definitions(self):
        return []
