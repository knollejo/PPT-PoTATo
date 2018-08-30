//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    LeptonCondition.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include <TMath.h>

#include "LeptonCondition.h"

LeptonCondition::LeptonCondition(
    float minpt,
    float maxpt,
    float mineta,
    float maxeta,
    bool cutelec,
    bool cutmuon,
    bool requireloose,
    bool invertloose,
    bool requiremedium,
    bool invertmedium,
    bool requiretight,
    bool inverttight,
    float miniso,
    float maxiso,
    float minmini,
    float maxmini
) :
    Condition<Lepton>(minpt, maxpt, mineta, maxeta),
    _cutElectrons(cutelec),
    _cutMuons(cutmuon),
    _requireLooseId(requireloose),
    _invertLooseId(invertloose),
    _requireMediumId(requiremedium),
    _invertMediumId(invertmedium),
    _requireTightId(requiretight),
    _invertTightId(inverttight),
    _minIso(miniso),
    _maxIso(maxiso),
    _minMiniIso(minmini),
    _maxMiniIso(maxmini)
{}

std::string LeptonCondition::getName() {
    if(_cutElectrons && !_cutMuons) return "ElectronCondition";
    else if(_cutMuons && !_cutElectrons) return "MuonCondition";
    else return "LeptonCondition";
}

bool LeptonCondition::check(Lepton* lep) {
    // Check lepton flavour
    if(!_cutElectrons && lep->isElectron()) return true;
    if(!_cutMuons && lep->isMuon()) return true;

    // Apply cuts on kinematics
    if(!Condition<Lepton>::check(lep)) return false;

    // Apply cuts
    if(_requireLooseId && _invertLooseId==lep->hasLooseId()) return false;
    if(_requireMediumId && _invertMediumId==lep->hasMediumId()) return false;
    if(_requireTightId && _invertTightId==lep->hasTightId()) return false;
    if((_minIso>0.0 && lep->relIso()<_minIso) || (_maxIso>0.0 && lep->relIso()>_maxIso)) return false;
    if((_minMiniIso>0.0 && lep->miniIso()<_minMiniIso) || (_maxMiniIso>0.0 && lep->miniIso()>_maxMiniIso)) return false;

    return true;
}
