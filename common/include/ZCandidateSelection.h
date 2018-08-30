//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    ZCandidateSelection.h
// Author:  Joscha Knolle
// Date:    2018-05-07
//----------------------------------------------------------------------------//

#ifndef PoTATo_trileptonic_ZCandidateSelection_h
#define PoTATo_trileptonic_ZCandidateSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class ZCandidateSelection : public Action {
public:
    ZCandidateSelection(bool, float, float);
    void initialize(Result*);
    float execute(Event*);
    void finalize(bool) {}
    std::string getName() { return "ZCandidateSelection"; }
    void selectedLeptons(int&, int&);

protected:
    // Configuration
    bool cutCandidate;
    float minMassDiff, trueZmass;

    // Data fields
    float massDilep, ptDilep, etaDilep, phiDilep, deltaPhiDilep;
    int positive, negative;
    bool passedZCandidate;

};

#endif // ifndef PoTATo_trileptonic_ZCandidateSelection_h
