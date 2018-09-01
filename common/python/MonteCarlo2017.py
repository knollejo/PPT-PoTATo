##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    MonteCarlo2017.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from InputFiles import InputFileCollection, InputFiles
from Mode import Mode
from Sample import Sample

MonteCarlo2017 = InputFileCollection()

MonteCarlo2017.ttzll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarZtollnunu.root',
    mode=Mode.TTbarZtoLLNuNu, sample=Sample.MC2017, nevents=1838397.29674, xsec=272.8#252.9
)
MonteCarlo2017.ttwjtoln = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarWjetstolnu_fall17.root',
    mode=Mode.TTbarWJetstoLNu, sample=Sample.MC2017, nevents=1687666.15467, xsec=204.3
)
MonteCarlo2017.tthtononbb = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarH125tononbbbar_fall17.root',
    mode=Mode.TTbarHtononBB, sample=Sample.MC2017, nevents=4484065.54236, xsec=215.1
)
MonteCarlo2017.ttgjets = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttgjets_fall17.root',
    mode=Mode.TTbarGJets, sample=Sample.MC2017, nevents=66911664.2488, xsec=3697.0
)
MonteCarlo2017.ttX = InputFiles(
    # MonteCarlo2017.ttzll,
    MonteCarlo2017.ttwjtoln, MonteCarlo2017.tthtononbb,
    MonteCarlo2017.ttgjets
)

MonteCarlo2017.ttdilep = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarsignalplustau_fromDilepton_fall17.root',
    mode=Mode.TTbarDilepton, sample=Sample.MC2017, nevents=627509941.344, xsec=87310.0
)
MonteCarlo2017.tt = InputFiles(MonteCarlo2017.ttdilep)

MonteCarlo2017.dyjtoll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/dy50inf_fall17_newpu.root',
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/dy50inf_fall17_oldpu.root',
    mode=Mode.DYJetsToLL, sample=Sample.MC2017, nevents=89157476302.7, xsec=5765400.0
)
MonteCarlo2017.wjetstoln = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wtolnu_fall17.root',
    mode=Mode.WJetsToLNu, sample=Sample.MC2017, nevents=76742756.0, xsec=61526700.0
)
MonteCarlo2017.vjets = InputFiles(
    MonteCarlo2017.dyjtoll, MonteCarlo2017.wjetstoln
)

MonteCarlo2017.zzto4l = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/zzto4l_fall17.root',
    mode=Mode.ZZto4L, sample=Sample.MC2017, nevents=2445271.52241, xsec=1256.0#1212.0
)
MonteCarlo2017.wzto3l = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wzto3l_fall17.root',
    mode=Mode.WZto3L, sample=Sample.MC2017, nevents=16442085.201733, xsec=4429.65#4429.65
)
MonteCarlo2017.vv = InputFiles(
    MonteCarlo2017.zzto4l, MonteCarlo2017.wzto3l,
)

MonteCarlo2017.zzztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/zzztoall_fall17.root',
    mode=Mode.ZZZtoAll, sample=Sample.MC2017, nevents=3504.65018255, xsec=13.98
)
MonteCarlo2017.wzztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wzztoall_fall17.root',
    mode=Mode.WZZtoAll, sample=Sample.MC2017, nevents=13945.5456336, xsec=55.65
)
MonteCarlo2017.wwztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wwztoall_fall17.root',
    mode=Mode.WWZtoAll, sample=Sample.MC2017, nevents=41200.4384502, xsec=165.1
)
MonteCarlo2017.vvv = InputFiles(
    MonteCarlo2017.zzztoall, MonteCarlo2017.wzztoall, MonteCarlo2017.wwztoall
)

MonteCarlo2017.tttt = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tttt_fall17.root',
    mode=Mode.FourTops, sample=Sample.MC2017, nevents=8162.88947219, xsec=9.103
)

MonteCarlo2017.tzqtoll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tzq_fall17.root',
    mode=Mode.TZQtoLL, sample=Sample.MC2017, nevents=162630.109078, xsec=94.18#75.8
)
MonteCarlo2017.tX = InputFiles(
    MonteCarlo2017.tzqtoll,
)

MonteCarlo2017.all = InputFiles(
    MonteCarlo2017.ttX, MonteCarlo2017.tt, MonteCarlo2017.vjets,
    MonteCarlo2017.vv, MonteCarlo2017.vvv, MonteCarlo2017.tttt,
    MonteCarlo2017.tX
)
