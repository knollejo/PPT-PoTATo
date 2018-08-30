##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    PostProcessor.py
## Author:  Joscha Knolle
## Date:    2018-05-14
##----------------------------------------------------------------------------##

from itertools import chain

from ROOT import gROOT

from EventStreams import EventStreams

class PostProcessor:

    def __init__(self, *inputs, **options):
        self.eventstreams = []
        self.add(*inputs)
        self.name = options.get('name', 'MyPostProcessor')
        self.path = options.get('path', '')
        self.replacements = []

    def add(self, *inputs):
        failed = []
        for obj in inputs:
            if isinstance(obj, (list, tuple)):
                self.add(*obj)
            elif EventStreams.isinstance(obj):
                self.eventstreams.append(obj)
            else:
                failed.append(obj)
        return failed

    @staticmethod
    def C_bool(b):
        return 'true' if b else 'false'

    @staticmethod
    def remove_duplicates(seq):
        seen = set()
        seen_add = seen.add
        return [x for x in seq if not (x in seen or seen_add(x))]

    def addIncludes(self, *inputs):
        self.C_includes += map(lambda i: '#include <{}>'.format(i), reduce(
            lambda x, y: x.union(y.Includes()), chain(*inputs), set()
        ))

    def addFields(self, *inputs):
        self.C_definitions += map(
            lambda f: 'TTreeReader{0}<{1}> {2} = {{_reader, "{2}"}};'.format(
                'Array' if f.is_array else 'Value', f.datatype, f.name
            ), reduce(
                lambda x, y: x.union(y.Fields()), chain(*inputs), set()
            )
        )

    def addDefinitions(self, *inputs):
        self.C_definitions += filter(None, reduce(lambda x, y: x+list(y), map(
            lambda i: i.Definitions(), chain(*inputs)
        ), []))

    def generate(self):
        self.C_includes = []
        self.C_definitions = []
        self.C_initializations = []
        self.C_constructions = []
        self.C_action = []
        self.C_outputs = []

        for nStream, stream in enumerate(self.eventstreams):
            self.C_definitions += map(lambda s: s.format(
                nStream=nStream, condition=stream.Condition(),
                weight=stream.Weight(), open=stream.Open(),
                close=stream.Close()
            ), [
                'TTree* open{nStream}() {{{open}}}',
                'void close{nStream}() {{{close}}}',
                'bool condition{nStream}() {{ return {condition}; }}',
                'double weight{nStream}() {{ return {weight}; }}',
            ])
            self.C_constructions += map(lambda s: s.format(
                nStream=nStream, name=self.name, title=stream.title
            ), [
                '_streams[{nStream}].open = &{name}::open{nStream};',
                '_streams[{nStream}].close = &{name}::close{nStream};',
                '_streams[{nStream}].condition = &{name}::condition{nStream};',
                '_streams[{nStream}].weight = &{name}::weight{nStream};',
                '_streams[{nStream}].title = "{title}";',
            ])

        self.addIncludes(self.eventstreams)
        self.addFields(self.eventstreams)
        self.addDefinitions(self.eventstreams)

    def finalize(self):
        with open('common/src/PostProcessor.cpp') as f:
            code = f.read()
        code = reduce(lambda c, (f, v): c.replace('/*$#{'+f+'}#$*/', v), chain(
            map(lambda f: (f, '\n'.join(
                self.remove_duplicates(getattr(self, 'C_'+f.lower()))
            )), (
                'INCLUDES', 'DEFINITIONS', 'INITIALIZATIONS', 'CONSTRUCTIONS',
                'ACTION', 'OUTPUTS',
            )), (
                ('NAME', self.name),
                ('NSTREAMS', str(len(self.eventstreams))),
            ), self.replacements,
        ), code)
        codefile = '{0}/{1}_main.C'.format(self.path, self.name)
        with open(codefile, 'w') as f:
            f.write(code)
        gROOT.ProcessLine('.x {0}+'.format(codefile))
