import common
MyAnalysis = common.Analyzer()

# Preselections
MyAnalysis.register(
    common.LeptonCondition(
        minPt=10.0, maxEta=2.4, requireMediumId=True
    ),
    common.ElectronToMuonDistance(mindistance=0.05),
    common.JetCondition(
        minPt=30.0, maxEta=2.4, btagWP=0.4941, cutPileup=True, pileupWP=4
    ),
    common.JetToLeptonDistance(mindistance=0.4),
)

# Process
process = common.Process(
    MyAnalysis,
    common.DataFiles2017.all, #+common.MonteCarlo2017.all,
    name='MyAnalysis_v1'
)
