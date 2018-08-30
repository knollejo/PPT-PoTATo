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
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarWjetstolnu.root',
    mode=Mode.TTbarWJetstoLNu, sample=Sample.MC2017, nevents=1687666.15467, xsec=204.3
)
MonteCarlo2017.tthtononbb = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarH125tononbbbar.root',
    mode=Mode.TTbarHtononBB, sample=Sample.MC2017, nevents=4316666.28764, xsec=215.1
)
MonteCarlo2017.ttgjets = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttgjets.root',
    mode=Mode.TTbarGJets, sample=Sample.MC2017, nevents=100040008.092, xsec=3697.0
)
MonteCarlo2017.ttX = InputFiles(
    MonteCarlo2017.ttzll, MonteCarlo2017.ttwjtoln, MonteCarlo2017.tthtononbb,
    MonteCarlo2017.ttgjets
)

MonteCarlo2017.ttdilep = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ttbarsignalplustau_fromDilepton.root',
    mode=Mode.TTbarDilepton, sample=Sample.MC2017, nevents=627509941.343, xsec=87310.0
)
MonteCarlo2017.tt = InputFiles(MonteCarlo2017.ttdilep)

MonteCarlo2017.dyj50toll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/dy50inf.root',
    mode=Mode.DYJetsToLL, sample=Sample.MC2017, nevents=3799457053531.021484, xsec=5765400.0
)
MonteCarlo2017.dyj10to50toll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/dy1050.root',
    mode=Mode.DYJetsToLL, sample=Sample.MC2017, nevents=38801157.0, xsec=18610000.0
)
MonteCarlo2017.dyjtoll = InputFiles(
    MonteCarlo2017.dyj50toll, MonteCarlo2017.dyj10to50toll
)
MonteCarlo2017.wjetstoln = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wtolnu.root',
    mode=Mode.WJetsToLNu, sample=Sample.MC2017, nevents=23219762.0, xsec=61526700.0
)
MonteCarlo2017.vjets = InputFiles(
    MonteCarlo2017.dyjtoll, MonteCarlo2017.wjetstoln
)

MonteCarlo2017.zzto4l = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/zzto4l.root',
    mode=Mode.ZZto4L, sample=Sample.MC2017, nevents=136031729.042, xsec=1256.0#1212.0
)
MonteCarlo2017.wzto3l = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wzto3l.root',
    mode=Mode.WZto3L, sample=Sample.MC2017, nevents=92523693.478, xsec=4670.0#4429.65
)
MonteCarlo2017.zgto2lg = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/zgto2lg.root',
    mode=Mode.ZGto2LG, sample=Sample.MC2017, nevents=549507145.32, xsec=131300.0#117864.0
)
MonteCarlo2017.wgtolnug = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wgtolnug.root',
    mode=Mode.WGtoLNuG, sample=Sample.MC2017, nevents=6103817, xsec=585800.0#489000.0
)
MonteCarlo2017.vv = InputFiles(
    MonteCarlo2017.zzto4l, MonteCarlo2017.wzto3l, MonteCarlo2017.zgto2lg,
    MonteCarlo2017.wgtolnug
)

MonteCarlo2017.zzztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/zzztoall.root',
    mode=Mode.ZZZtoAll, sample=Sample.MC2017, nevents=3504.65018256, xsec=13.98
)
MonteCarlo2017.wzztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wzztoall.root',
    mode=Mode.WZZtoAll, sample=Sample.MC2017, nevents=13945.5456336, xsec=55.65
)
MonteCarlo2017.wwztoall = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/wwztoall.root',
    mode=Mode.WWZtoAll, sample=Sample.MC2017, nevents=41200.4384502, xsec=165.1
)
MonteCarlo2017.vvv = InputFiles(
    MonteCarlo2017.zzztoall, MonteCarlo2017.wzztoall, MonteCarlo2017.wwztoall
)

MonteCarlo2017.tttt = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tttt.root',
    mode=Mode.FourTops, sample=Sample.MC2017, nevents=8162.88947219, xsec=9.103
)

MonteCarlo2017.tzqtoll = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tzq.root',
    mode=Mode.TZQtoLL, sample=Sample.MC2017, nevents=985135.258325, xsec=94.18#75.8
)
MonteCarlo2017.twll_top = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tw_top.root',
    mode=Mode.SingleTopWLL, sample=Sample.MC2017, nevents=172840521.219, xsec=19.47
)
MonteCarlo2017.twll_antitop = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/tw_antitop.root',
    mode=Mode.SingleTopWLL, sample=Sample.MC2017, nevents=401485143.201, xsec=19.47
)
MonteCarlo2017.twll = InputFiles(
    MonteCarlo2017.twll_top, MonteCarlo2017.twll_antitop
)
MonteCarlo2017.tX = InputFiles(
    MonteCarlo2017.tzqtoll, MonteCarlo2017.twll
)

MonteCarlo2017.all = InputFiles(
    MonteCarlo2017.ttX, MonteCarlo2017.tt, MonteCarlo2017.vjets,
    MonteCarlo2017.vv, MonteCarlo2017.vvv, MonteCarlo2017.tttt,
    MonteCarlo2017.tX
)
