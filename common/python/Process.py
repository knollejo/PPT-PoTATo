##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    Process.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from datetime import datetime
from os import getcwd, mkdir
from os.path import exists
from subprocess import call

from ROOT import TChain, TFile

from Analyzer import Analyzer
from InputFiles import InputFiles
from Mode import Mode
from ResourcesManager import ResourcesManager
from Sample import Sample

class Process:

    def __init__(self, *inputs, **options):
        self.analyzer = None
        self.inputfiles = None
        for obj in inputs:
            if not self.analyzer and isinstance(obj, Analyzer):
                self.analyzer = obj
            elif isinstance(obj, InputFiles):
                self.inputfiles += obj
        self.name = options.get('name', 'process')
        self.script = options.get('script', None)
        self.mail = options.get('mail', None)
        self.successmail = options.get('successmail', False)
        self.hours = options.get('hours', None)
        self.vmem = options.get('vmem', None)
        self.treename = options.get('treename', 'writeNTuple/NTuple')

    def run(self, name=None, mode=None, sample=None, part=None, boundaries=None):
        if not exists('output'):
            mkdir('output')
        outputname = 'output/{0}.root'.format('_'.join(filter(None, (
            name, Mode.getName(mode), Sample.getName(sample),
            'part{0}'.format(part) if part is not None else None
        ))))
        self.analyzer.writeOutput(outputname)
        self.analyzer.initialize()
        res = ResourcesManager()
        if part is None:
            for f,m,s,x,n in self.inputfiles.iterate(mode=mode, sample=sample):
                inputfile = TFile.Open(f)
                tree = inputfile.Get(self.treename)
                res.registerFile(inputfile)
                self.analyzer.process(tree, m, s, x, n, res=res)
                inputfile.Close()
        else:
            nentries = 0
            for f,m,s,x,n in self.inputfiles.iterate(mode=mode, sample=sample):
                inputfile = TFile.Open(f)
                tree = inputfile.Get(self.treename)
                thisentries = tree.GetEntries()
                if nentries+thisentries>boundaries[0] and nentries<boundaries[1]:
                    first = max(0, boundaries[0]-nentries)
                    last = min(thisentries, boundaries[1]-nentries)
                    res.registerFile(inputfile)
                    self.analyzer.process(
                        tree, m, s, x, n, res=res, boundaries=(first, last)
                    )
                inputfile.Close()
                nentries += thisentries
        self.analyzer.finalize()

    def submit(self, **options):
        name = options.get('name', self.name)
        script = options.get('script', self.script)
        mail = options.get('mail', self.mail)
        successmail = options.get('successmail', self.successmail)
        hours = options.get('hours', self.hours)
        vmem = options.get('vmem', self.vmem)
        timestamp = datetime.now().strftime('%y%m%d_%H%M%S')
        cwd = getcwd()
        if not exists('log'):
            mkdir('log')
        settings = []
        if mail:
            settings += ['-m', 'eas' if successmail else 'as', '-M', mail]
        if hours:
            settings += ['-l', 'h_rt="{0}:00:00"'.format(hours)]
        if vmem:
            settings += ['-l', 'h_vmem="{0}"'.format(vmem)]
        settings += ['job.sh', cwd, script]
        for m, s in set(map(lambda f: (f[1], f[2]), self.inputfiles.files)):
            chain = TChain(self.treename)
            map(lambda f: chain.Add(f[0]), list(
                self.inputfiles.iterate(mode=m, sample=s)
            ))
            nentries = chain.GetEntries()
            nparts = max(1, nentries/1500000)
            boundaries = (lambda l: zip(l, l[1:]))([
                i*nentries/nparts for i in range(nparts+1)
            ])
            for part, (upper, lower) in enumerate(boundaries):
                partl = 'part{0}'.format(part)
                command = ['qsub -j y -o']
                command.append('{0}/log/{1}.txt'.format(cwd, '_'.join(filter(
                    None,
                    (name, Mode.getName(m), Sample.getName(s), partl, timestamp)
                ))))
                command += ['-N', '.'.join(filter(
                    None, (name, Mode.getName(m), Sample.getName(s), partl)
                ))]
                command += settings
                command.append(name)
                command += map(str, (m, s, part, upper, lower))
                # print ' '.join(command)
                call(' '.join(command), shell=True)
