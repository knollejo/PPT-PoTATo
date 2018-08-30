//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    ElectronToMuonDistance.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_ElectronToMuonDistance_h
#define PoTATo_common_ElectronToMuonDistance_h

#include <string>

#include "Event.h"
#include "Lepton.h"
#include "MinDistancePreselection.h"
#include "Vector.h"

class ElectronToMuonDistance : public MinDistancePreselection<Lepton> {
public:
    ElectronToMuonDistance(float);
    ~ElectronToMuonDistance();
    std::string getName() { return "ElectronToMuonDistance"; }

protected:
    void setup(Event* ev);
    int nProbes() { return _nElectrons; }
    int nRefs(int) { return _nMuons; }
    Vector* getProbe(int nProbe) { return _event->lepton(_electrons[nProbe]); }
    Vector* getRef(int nRef, int) { return _event->lepton(_muons[nRef]); }
    void removeProbe(int nProbe) { _event->removeLepton(_electrons[nProbe]); }

    Event* _event;
    int _nElectrons, _nMuons;
    int* _electrons = nullptr;
    int* _muons = nullptr;

};

#endif // ifndef TTZ_ElectronToMuonDistance_h
