//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    ElectronToMuonDistance.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "ElectronToMuonDistance.h"

ElectronToMuonDistance::ElectronToMuonDistance(float mind) :
    MinDistancePreselection<Lepton>(mind)
{
    _electrons = new int[10];
    _muons = new int[10];
}

ElectronToMuonDistance::~ElectronToMuonDistance() {
    if(_electrons!=nullptr) delete [] _electrons;
    if(_muons!=nullptr) delete [] _muons;
}

void ElectronToMuonDistance::setup(Event* ev) {
    _event = ev;
    _nElectrons = 0;
    _nMuons = 0;
    for(int nLep=0; nLep<_event->nLeptons(); nLep++) {
        if(_event->lepton(nLep)->isElectron()) {
            _electrons[_nElectrons++] = nLep;
        } else if(_event->lepton(nLep)->isMuon()) {
            _muons[_nMuons++] = nLep;
            _efficiency.pass();
        }
    }
}
