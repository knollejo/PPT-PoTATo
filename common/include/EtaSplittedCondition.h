//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EtaSplittedCondition.h
// Author:  Joscha Knolle
// Date:    2018-04-26
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_EtaSplittedCondition_h
#define PoTATo_common_EtaSplittedCondition_h

#include <string>

#include "Condition.h"
#include "Event.h"
#include "Result.h"

template <typename T> class EtaSplittedCondition : public Condition<T> {
public:
    EtaSplittedCondition(float eta, Condition<T>* c1, Condition<T>* c2) : Condition<T>(-1.0, -1.0, -1.0, -1.0), _eta(eta), _cond1(c1), _cond2(c2) {}
    virtual ~EtaSplittedCondition() { delete _cond1; delete _cond2; }
    virtual void initialize(Result* res) { _cond1->initialize(res); _cond2->initialize(res); }
    // virtual void finalize(bool writeFile) { _cond1->finalize(writeFile); _cond2->finalize(writeFile); }
    virtual std::string getName() { return "EtaSplitted"+_cond1->getName(); }

    virtual bool check(T*);

protected:
    float _eta;
    Condition<T>* _cond1, * _cond2;

};

#endif // ifndef PoTATo_common_EtaSplittedCondition_h
