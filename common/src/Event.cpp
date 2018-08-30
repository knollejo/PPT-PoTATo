//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Event.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include <algorithm>

#include "Event.h"

Event::Event(Event& other) :
    _mode(other._mode),
    _sample(other._sample),
    _runNumber(other._runNumber),
    _lumiBlock(other._lumiBlock),
    _eventNumber(other._eventNumber),
    _trigger_smu(other._trigger_smu),
    _trigger_se(other._trigger_se),
    _trigger_mumu(other._trigger_mumu),
    _trigger_emu(other._trigger_emu),
    _trigger_ee(other._trigger_ee),
    _leptons(other._leptons),
    _jets(other._jets),
    _met(other._met),
    _n_vertices(other._n_vertices),
    _n_first_vertices(other._n_first_vertices)
{
    other._leptons = 0;
    other._jets = 0;
    other._met = 0;
}

Event::~Event() {
    if(_leptons!=nullptr) {
        for(std::vector<Lepton*>::iterator lepton=_leptons->begin(); lepton!=_leptons->end(); ++lepton) {
            if(!*lepton) delete (*lepton);
        }
        delete _leptons;
    }
    if(_jets!=nullptr) {
        for(std::vector<Jet*>::iterator jet=_jets->begin(); jet!=_jets->end(); ++jet) {
            if(!*jet) delete (*jet);
        }
        delete _jets;
    }
    if(_met!=nullptr)
        delete _met;
}

void Event::trigger(unsigned int& smu, unsigned int& se, unsigned int& mumu, unsigned int& emu, unsigned int& ee) {
    smu = _trigger_smu;
    se = _trigger_se;
    mumu = _trigger_mumu;
    emu = _trigger_emu;
    ee = _trigger_ee;
}

void Event::removeLepton(int i) {
    delete (_leptons->at(i));
    _leptons->erase(_leptons->begin()+i);
}

void Event::sortLeptons() {
    std::sort(_leptons->begin(), _leptons->end(), Vector::ptOrder);
}

void Event::removeJet(int i) {
    delete (_jets->at(i));
    _jets->erase(_jets->begin()+i);
}

void Event::sortJets() {
    std::sort(_jets->begin(), _jets->end(), Vector::ptOrder);
}
