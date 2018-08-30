//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Lepton.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include <TMath.h>

#include "Lepton.h"

Lepton::Lepton(
    LorentzVector lv,
    int pdgid,
    bool idloose,
    bool idmedium,
    bool idtight,
    double pfiso,
    double miniiso
) :
    Vector(lv),
    _pdgId(pdgid),
    _idLoose(idloose),
    _idMedium(idmedium),
    _idTight(idtight),
    _pfIso(pfiso),
    _miniIso(miniiso)
{}

std::string Lepton::getType() {
    if(isElectron()) return "lepton:electron";
    else if(isMuon()) return "lepton:muon";
    else return "lepton";
}

bool Lepton::isElectron() {
    return bool(TMath::Abs(_pdgId) == ELECTRON_PDG);
}

bool Lepton::isMuon() {
    return bool(TMath::Abs(_pdgId) == MUON_PDG);
}
