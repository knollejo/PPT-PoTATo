//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MissingEtSelection.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_MissingEtSelection_h
#define PoTATo_common_MissingEtSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class MissingEtSelection : public Action {
public:
    MissingEtSelection(bool, double, double);
    void initialize(Result*);
    float execute(Event*);
    void finalize(bool) {}
    std::string getName() { return "MissingEtSelection"; }

protected:
    bool _cutMissingEt, _passedMissingEt;
    double _minMet, _maxMet;
    float _met;

};

#endif // ifndef PoTATo_common_MissingEtSelection_h
