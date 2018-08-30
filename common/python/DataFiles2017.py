##----------------------------------------------------------------------------##
## PoTATo's a Top Analysis Tool
## Project: common
## File:    DataFiles2017.py
## Author:  Joscha Knolle
## Date:    2018-04-30
##----------------------------------------------------------------------------##

from InputFiles import InputFileCollection, InputFiles
from Mode import Mode
from Sample import Sample

DataFiles2017 = InputFileCollection()

DataFiles2017.Bee = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ee_run2017B.root',
    mode=Mode.DoubleElectron, sample=Sample.Run2017B
)
DataFiles2017.Bemu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/emu_run2017B.root',
    mode=Mode.ElectronMuon, sample=Sample.Run2017B
)
DataFiles2017.Bmumu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/mumu_run2017B.root',
    mode=Mode.DoubleMuon, sample=Sample.Run2017B
)
DataFiles2017.Bse = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/se_run2017B.root',
    mode=Mode.SingleElectron, sample=Sample.Run2017B
)
DataFiles2017.Bsmu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/smu_run2017B.root',
    mode=Mode.SingleMuon, sample=Sample.Run2017B
)
DataFiles2017.B = InputFiles(
    DataFiles2017.Bee, DataFiles2017.Bemu, DataFiles2017.Bmumu,
    DataFiles2017.Bse, DataFiles2017.Bsmu
)

DataFiles2017.Cee = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ee_run2017C.root',
    mode=Mode.DoubleElectron, sample=Sample.Run2017C
)
DataFiles2017.Cemu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/emu_run2017C.root',
    mode=Mode.ElectronMuon, sample=Sample.Run2017C
)
DataFiles2017.Cmumu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/mumu_run2017C.root',
    mode=Mode.DoubleMuon, sample=Sample.Run2017C
)
DataFiles2017.Cse = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/se_run2017C.root',
    mode=Mode.SingleElectron, sample=Sample.Run2017C
)
DataFiles2017.Csmu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/smu_run2017C.root',
    mode=Mode.SingleMuon, sample=Sample.Run2017C
)
DataFiles2017.C = InputFiles(
    DataFiles2017.Cee, DataFiles2017.Cemu, DataFiles2017.Cmumu,
    DataFiles2017.Cse, DataFiles2017.Csmu
)

DataFiles2017.Dee = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ee_run2017D.root',
    mode=Mode.DoubleElectron, sample=Sample.Run2017D
)
DataFiles2017.Demu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/emu_run2017D.root',
    mode=Mode.ElectronMuon, sample=Sample.Run2017D
)
DataFiles2017.Dmumu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/mumu_run2017D.root',
    mode=Mode.DoubleMuon, sample=Sample.Run2017D
)
DataFiles2017.Dse = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/se_run2017D.root',
    mode=Mode.SingleElectron, sample=Sample.Run2017D
)
DataFiles2017.Dsmu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/smu_run2017D.root',
    mode=Mode.SingleMuon, sample=Sample.Run2017D
)
DataFiles2017.D = InputFiles(
    DataFiles2017.Dee, DataFiles2017.Demu, DataFiles2017.Dmumu,
    DataFiles2017.Dse, DataFiles2017.Dsmu
)

DataFiles2017.Eee = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ee_run2017E.root',
    mode=Mode.DoubleElectron, sample=Sample.Run2017E
)
DataFiles2017.Eemu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/emu_run2017E.root',
    mode=Mode.ElectronMuon, sample=Sample.Run2017E
)
DataFiles2017.Emumu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/mumu_run2017E.root',
    mode=Mode.DoubleMuon, sample=Sample.Run2017E
)
DataFiles2017.Ese = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/se_run2017E.root',
    mode=Mode.SingleElectron, sample=Sample.Run2017E
)
DataFiles2017.Esmu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/smu_run2017E.root',
    mode=Mode.SingleMuon, sample=Sample.Run2017E
)
DataFiles2017.E = InputFiles(
    DataFiles2017.Eee, DataFiles2017.Eemu, DataFiles2017.Emumu,
    DataFiles2017.Ese, DataFiles2017.Esmu
)

DataFiles2017.Fee = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/ee_run2017F.root',
    mode=Mode.DoubleElectron, sample=Sample.Run2017F
)
DataFiles2017.Femu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/emu_run2017F.root',
    mode=Mode.ElectronMuon, sample=Sample.Run2017F
)
DataFiles2017.Fmumu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/mumu_run2017F.root',
    mode=Mode.DoubleMuon, sample=Sample.Run2017F
)
DataFiles2017.Fse = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/se_run2017F.root',
    mode=Mode.SingleElectron, sample=Sample.Run2017F
)
DataFiles2017.Fsmu = InputFiles(
    '/nfs/dust/cms/user/knollejo/cms/94X/ppt_v1/smu_run2017F.root',
    mode=Mode.SingleMuon, sample=Sample.Run2017F
)
DataFiles2017.F = InputFiles(
    DataFiles2017.Fee, DataFiles2017.Femu, DataFiles2017.Fmumu,
    DataFiles2017.Fse, DataFiles2017.Fsmu
)

DataFiles2017.ee = InputFiles(
    DataFiles2017.Bee, DataFiles2017.Cee, DataFiles2017.Dee,
    DataFiles2017.Eee, DataFiles2017.Fee
)
DataFiles2017.emu = InputFiles(
    DataFiles2017.Bemu, DataFiles2017.Cemu, DataFiles2017.Demu,
    DataFiles2017.Eemu, DataFiles2017.Femu
)
DataFiles2017.mumu = InputFiles(
    DataFiles2017.Bmumu, DataFiles2017.Cmumu, DataFiles2017.Dmumu,
    DataFiles2017.Emumu, DataFiles2017.Fmumu
)
DataFiles2017.se = InputFiles(
    DataFiles2017.Bse, DataFiles2017.Cse, DataFiles2017.Dse,
    DataFiles2017.Ese, DataFiles2017.Fse
)
DataFiles2017.smu = InputFiles(
    DataFiles2017.Bsmu, DataFiles2017.Csmu, DataFiles2017.Dsmu,
    DataFiles2017.Esmu, DataFiles2017.Fsmu
)

DataFiles2017.all = InputFiles(
    DataFiles2017.ee, DataFiles2017.emu, DataFiles2017.mumu,
    DataFiles2017.se, DataFiles2017.smu
)
