//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    JetCondition.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_JetCondition_h
#define PoTATo_common_JetCondition_h

#include <string>

#include "Condition.h"
#include "Jet.h"

class JetCondition : public Condition<Jet> {
public:
    JetCondition(float, float, float, float, bool, bool, int, float, float, float);
    virtual ~JetCondition() {}
    virtual std::string getName() { return "JetCondition"; }

    virtual bool check(Jet*);
    
protected:
    bool _cutPileup, _invertPileup;
    int _pileupWP;
    float _btagWP, _minBtag, _maxBtag;

};

#endif // ifndef PoTATo_common_JetCondition_h
