//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Wboson.cpp
// Author:  Joscha Knolle
// Date:    2018-04-23
//----------------------------------------------------------------------------//

#include "Wboson.h"

Wboson::Wboson(LorentzVector lv, int decaymode, Lepton* lepton, Vector* neutrino):
    Vector(lv),
    _decayMode(decaymode),
    _lepton(lepton),
    _neutrino(neutrino)
{}

Wboson::~Wboson() {
    if(_lepton!=nullptr) delete _lepton;
    if(_neutrino!=nullptr) delete _neutrino;
}
