//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Condition.cpp
// Author:  Joscha Knolle
// Date:    2018-04-30
//----------------------------------------------------------------------------//

#include <TMath.h>

#include "Condition.h"
#include "Jet.h"
#include "Lepton.h"
#include "Vector.h"

template <typename T> Condition<T>::Condition(
    float minpt,
    float maxpt,
    float mineta,
    float maxeta
):
    _minPt(minpt),
    _maxPt(maxpt),
    _minEta(mineta),
    _maxEta(maxeta)
{}

template <typename T> float Condition<T>::execute(Event* ev) {
    for(int i=size(ev)-1; i>=0; i--) {
        if(!check(object(ev, i))) {
            remove(ev, i);
            _efficiency.fail();
        }
        else _efficiency.pass();
    }
    return 1.0;
}

template <typename T> bool Condition<T>::check(T* test) {
    // Apply cuts
    if((_minPt>0.0 && test->Pt()<_minPt) || (_maxPt>0.0 && test->Pt()>_maxPt)) return false;
    if((_minEta>0.0 && TMath::Abs(test->Eta())<_minEta) || (_maxEta>0.0 && TMath::Abs(test->Eta())>_maxEta)) return false;

    return true;
}

// Specialization for leptons
template<> int Condition<Lepton>::size(Event* ev) {
    return ev->nLeptons();
}
template<> Lepton* Condition<Lepton>::object(Event* ev, int i) {
    return ev->lepton(i);
}
template<> void Condition<Lepton>::remove(Event* ev, int i) {
    return ev->removeLepton(i);
}
template <> std::string Condition<Lepton>::directoryName() {
    return "leptonEfficiencies";
}
template class Condition<Lepton>;

// Specialization for jets
template<> int Condition<Jet>::size(Event* ev) {
    return ev->nJets();
}
template<> Jet* Condition<Jet>::object(Event* ev, int i) {
    return ev->jet(i);
}
template<> void Condition<Jet>::remove(Event* ev, int i) {
    return ev->removeJet(i);
}
template <> std::string Condition<Jet>::directoryName() {
    return "jetEfficiencies";
}
template class Condition<Jet>;
