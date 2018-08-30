##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Field.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

class Field:

    def __init__(self, name, datatype='float', is_array=False):
        self.name = name
        self.is_array = is_array
        self.datatype = datatype

    def __eq__(self, other):
        if (
            self.name == other.name and self.is_array == other.is_array
            and self.datatype == other.datatype
        ):
            return True
        elif self.name == other.name:
            raise RuntimeError((
                'Try to call branch {0} with different properties: '
                '{1}{2} vs. {3}{4}'
            ).format(
                self.name, self.datatype, '[]' if self.is_array else '',
                other.datatype, '[]' if other.is_array else ''
            ))
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash(self.name)
