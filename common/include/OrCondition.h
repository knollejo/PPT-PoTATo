//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    OrCondition.h
// Author:  Joscha Knolle
// Date:    2018-04-26
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_OrCondition_h
#define PoTATo_common_OrCondition_h

#include <string>

#include "Condition.h"

template <typename T> class OrCondition : public Condition<T> {
public:
    OrCondition(Condition<T>* c1, Condition<T>* c2) : Condition<T>(-1.0, -1.0, -1.0, -1.0), _cond1(c1), _cond2(c2) {}
    virtual ~OrCondition() { delete _cond1; delete _cond2; }
    virtual void initialize(Result* res) { _cond1->initialize(res); _cond2->initialize(res); }
    // virtual void finalize(bool writeFile) { _cond1->finalize(writeFile); _cond2->finalize(writeFile); }
    virtual std::string getName() { return _cond1->getName()+"Or"+_cond2->getName(); }

    virtual bool check(T* test) { return _cond1->check(test) || _cond2->check(test); }

protected:
    Condition<T>* _cond1, * _cond2;

};

#endif // ifndef PoTATo_common_OrCondition_h
