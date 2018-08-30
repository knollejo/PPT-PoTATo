##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Category.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from Plotable import Plotable

class Category(Plotable):

    def __init__(self, **options):
        Plotable.__init__(self, **options)

    def __mul__(self, other):
        # Combine fields
        fields = self.Fields().union(other.Fields())

        # Combine includes
        includes = self.Includes().union(other.Includes())

        # Combine labels
        label = ', '.join(filter(None, (self.label, other.label)))
        latexlabel = ', '.join(filter(
            None, (self.latexlabel, other.latexlabel)
        ))
        short = '_'.join(filter(None, (self.short, other.short)))

        # Combine conditions
        condition = reduce(
            lambda c1, c2: '({0}) && ({1})'.format(c1, c2),
            filter(None, (self.Condition(), other.Condition())),
            'true'
        )

        # Combine weights
        weight = reduce(
            lambda w1, w2: '({0})*({1})'.format(w1, w2),
            filter(None, (self.Weight(), other.Weight())),
            '1.0'
        )

        # Return combined category
        result = Category(
            fields=fields, includes=includes, label=label, latexlabel=latexlabel,
            short=short, labelformat=self.labelformat, condition=condition,
            weight=weight, name=self.name, title=self.title
        )
        return result
