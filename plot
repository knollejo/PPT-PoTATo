#!/usr/bin/env python

from sys import argv
if not '-b' in argv:
    argv.append('-b')

from imp import load_source
from os import mkdir
from os.path import abspath, dirname, exists

import common

if len(argv)<2 or not exists(argv[1]):
    raise RuntimeError('Need to specify config file!')
config = load_source('myconfig', argv[1])
managers = []
for __, obj in config.__dict__.iteritems():
    if isinstance(obj, common.PlotManager):
        managers.append(obj)
if not managers:
    raise RuntimeError('Need to specify PlotManager object in config file!')
name = ''.join(map(lambda s: s if s.isalnum() else '_', argv[1]))
path = dirname(abspath(argv[1]))
if path[-1] != '/':
    path = path+'/'
path = path+'temp'
if not exists(path):
    mkdir(path)
for i, obj in enumerate(managers):
    obj.name = '{0}_{1}'.format(name, i)
    obj.path = path
    obj.generate()
    obj.finalize()
