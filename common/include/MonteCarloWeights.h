//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MonteCarloWeights.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_MonteCarloWeights_h
#define PoTATo_common_MonteCarloWeights_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class MonteCarloWeights : public Action {
public:
    void initialize(Result*) {}
    float execute(Event*);
    void finalize(bool) {}
    std::string getName() { return "MonteCarloWeights"; }

};

#endif // ifndef TTZ_MonteCarloWeights_h
