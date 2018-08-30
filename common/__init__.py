##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    __init__.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

import __builtin__
from os import listdir
from os.path import abspath, dirname
import ROOT

# Path to header files
path = dirname(abspath(__file__))
ROOT.gROOT.ProcessLine('.include {0}/include/'.format(path))

if getattr(__builtin__, 'TTZ_Compile_Switch_'+__name__, False):
    setattr(__builtin__, 'TTZ_Compile_Switch_'+__name__, False)

    # Compile command
    command = '.L {0}/src/{1}+'
    if getattr(__builtin__, 'TTZ_Compile_All_Switch_'+__name__, False):
        command = command+'+'

    # Compile all files
    for filename in (
        'Lepton.cpp',
        'Jet.cpp',
        'MissingEt.cpp',
        'RenameAction.cpp',
        'EfficiencyCounter.cpp',
        'Condition.cpp',
        'OrCondition.cpp',
        'EtaSplittedCondition.cpp',
        'LeptonCondition.cpp',
        'JetCondition.cpp',
        'Event.cpp',
        'Result.cpp',
        'EventReader.cpp',
        'Analyzer.cpp',
        'TriggerSelection.cpp',
        'FirstVertexSelection.cpp',
        'MinDistancePreselection.cpp',
        'JetToLeptonDistance.cpp',
        'ElectronToMuonDistance.cpp',
        'MonteCarloWeights.cpp',
        'MissingEtSelection.cpp',
        'JetSelection.cpp',
        'LeptonSelection.cpp',
        'ZCandidateSelection.cpp',
        'TrileptonTrigger.cpp',
    ):
        ROOT.gROOT.ProcessLine(command.format(path, filename))

else:
    # Load compiled files from src
    for filename in [f for f in listdir('{0}/src/'.format(path)) if f.endswith('.so')]:
        ROOT.gROOT.ProcessLine('.L {0}/src/{1}'.format(path, filename))

# Load modules from ./python subdirectory to this package
from python import *
