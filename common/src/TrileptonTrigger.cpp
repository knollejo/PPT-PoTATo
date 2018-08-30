//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: trileptonic
// File:    TrileptonTrigger.cpp
// Author:  Joscha Knolle
// Date:    2018-05-07
//----------------------------------------------------------------------------//

#include "Mode.h"
#include "Sample.h"
#include "TrileptonTrigger.h"

namespace {
    using namespace TriggerMap;

    const int SingleMuon_2017 =
          SMu::HLT_IsoMu27
        | SMu::HLT_IsoMu30
        | SMu::HLT_Mu50
        | SMu::HLT_Mu55;
    const int SingleElectron_2017 =
          SE::HLT_Ele32_WPTight_Gsf
        | SE::HLT_Ele35_WPTight_Gsf
        | SE::HLT_Ele38_WPTight_Gsf
        | SE::HLT_Ele40_WPTight_Gsf
        | SE::HLT_Ele115_CaloIdVT_GsfTrkIdT
        | SE::HLT_Photon200;
    const int DoubleMuon_2017 =
          MuMu::HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8
        | MuMu::HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8
        | MuMu::HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8
        | MuMu::HLT_TripleMu_10_5_5_DZ
        | MuMu::HLT_TripleMu_5_3_3_Mass3p8to60_DZ
        | MuMu::HLT_TripleMu_12_10_5;
    const int ElectronMuon_2017 =
          EMu::HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL
        | EMu::HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ
        | EMu::HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ
        | EMu::HLT_Mu8_DiEle12_CaloIdL_TrackIdL
        | EMu::HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ
        | EMu::HLT_DiMu9_Ele9_CaloIdL_TrackIdL
        | EMu::HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ;
    const int DoubleElectron_2017 =
          EE::HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL
        | EE::HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ
        | EE::HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;

}

void TrileptonTrigger::initialize(Result* res) {
    TriggerSelection::initialize(res);
    res->branch("triggeredSingleMuon", &_triggeredSingleMuon);
    res->branch("triggeredSingleElectron", &_triggeredSingleElectron);
    res->branch("triggeredDoubleMuon", &_triggeredDoubleMuon);
    res->branch("triggeredDoubleElectron", &_triggeredDoubleElectron);
    res->branch("triggeredElectronMuon", &_triggeredElectronMuon);
}

Mode::Type TrileptonTrigger::checkTriggers(
    Sample::Type sample, Mode::Type mode, unsigned int smu, unsigned int se,
    unsigned int mumu, unsigned int emu, unsigned int ee
) {
    Mode::Type triggered = 0;

    // Single Muon triggers
    if((sample&(Sample::Run2017|Sample::MC2017))!=0) {
        if((smu&SingleMuon_2017)!= 0)
            triggered = triggered|Mode::SingleMuon;
    }
    _triggeredSingleMuon = (triggered&Mode::SingleMuon)!=0;

    // Single Electron triggers
    if((sample&(Sample::Run2017|Sample::MC2017))!=0) {
        if((se&SingleElectron_2017)!=0)
            triggered = triggered|Mode::SingleElectron;
    }
    _triggeredSingleElectron = (triggered&Mode::SingleElectron)!=0;

    // Double Muon triggers
    if((sample&(Sample::Run2017|Sample::MC2017))!=0) {
        if((mumu&DoubleMuon_2017)!=0)
            triggered = triggered|Mode::DoubleMuon;
    }
    _triggeredDoubleMuon = (triggered&Mode::DoubleMuon)!=0;

    // Electron Muon triggers
    if((sample&(Sample::Run2017|Sample::MC2017))!=0) {
        if((emu&ElectronMuon_2017)!=0)
            triggered = triggered|Mode::ElectronMuon;
    }
    _triggeredElectronMuon = (triggered&Mode::ElectronMuon)!=0;

    // Double Electron triggers
    if((sample&(Sample::Run2017|Sample::MC2017))!=0) {
        if((ee&DoubleElectron_2017)!=0)
            triggered = triggered|Mode::DoubleElectron;
    }
    _triggeredDoubleElectron = (triggered&Mode::DoubleElectron)!=0;

    // make samples exclusive
    switch(mode) {
        case Mode::SingleMuon:
            break;
        case Mode::SingleElectron:
            if(_triggeredSingleMuon)
                triggered = 0;
            break;
        case Mode::DoubleMuon:
            if(_triggeredSingleMuon||_triggeredSingleElectron)
                triggered = 0;
            break;
        case Mode::DoubleElectron:
            if(_triggeredSingleMuon||_triggeredSingleElectron||_triggeredDoubleMuon)
                triggered = 0;
            break;
        case Mode::ElectronMuon:
            if(_triggeredSingleMuon||_triggeredSingleElectron||_triggeredDoubleMuon||_triggeredDoubleElectron)
                triggered = 0;
            break;
        default:
            break;
    }
    return triggered;
}
