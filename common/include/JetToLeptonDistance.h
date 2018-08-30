//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    JetToLeptonDistance.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_JetToLeptonDistance_h
#define PoTATo_common_JetToLeptonDistance_h

#include <string>

#include "Event.h"
#include "MinDistancePreselection.h"
#include "Jet.h"
#include "Vector.h"

class JetToLeptonDistance : public MinDistancePreselection<Jet> {
public:
    JetToLeptonDistance(double mind) : MinDistancePreselection<Jet>(mind) {}
    std::string getName() { return "JetToLeptonDistance"; }

protected:
    void setup(Event* ev) { _event = ev;  }
    int nProbes() { return _event->nJets(); }
    int nRefs(int) { return _event->nLeptons(); }
    Vector* getProbe(int nProbe) { return _event->jet(nProbe); }
    Vector* getRef(int nRef, int) { return _event->lepton(nRef); }
    void removeProbe(int nProbe) { _event->removeJet(nProbe); }

    Event* _event;

};

#endif // ifndef PoTATo_common_JetToLeptonDistance_h
