//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MinDistancePreselection.cpp
// Author:  Joscha Knolle
// Date:    2018-05-08
//----------------------------------------------------------------------------//

#include "Jet.h"
#include "Lepton.h"
#include "MinDistancePreselection.h"

template <typename T> float MinDistancePreselection<T>::execute(Event* ev) {
    setup(ev);
    bool* failed = new bool[nProbes()];

    // Test all probes against all reference objects
    for(int nProbe=0; nProbe<nProbes(); nProbe++) {
        Vector* probe = getProbe(nProbe);
        failed[nProbe] = false;
        for(int nRef=0; nRef<nRefs(nProbe); nRef++) {
            Vector* ref = getRef(nRef, nProbe);
            if(probe->DeltaR(*ref)<_mindistance) {
                failed[nProbe] = true;
                break;
            }
        }
    }

    // Remove probes that failed
    for(int nProbe=nProbes()-1; nProbe>=0; nProbe--) {
        if(failed[nProbe]) {
            removeProbe(nProbe);
            _efficiency.fail();
        } else _efficiency.pass();
    }
    delete [] failed;
    return 1.0;
}

// Instantiate specializations
template class MinDistancePreselection<Lepton>;
template class MinDistancePreselection<Jet>;
