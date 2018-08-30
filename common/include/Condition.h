//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Condition.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Condition_h
#define PoTATo_common_Condition_h

#include <string>

#include "Action.h"
#include "EfficiencyCounter.h"
#include "Event.h"
#include "Result.h"

template <typename T> class Condition : public Action {
public:
    Condition(float, float, float, float);
    virtual ~Condition() {}
    virtual void initialize(Result*) {}
    virtual float execute(Event* ev);
    virtual void finalize(bool writeFile) { if(writeFile) _efficiency.write(getName()); }

    virtual bool check(T*);

protected:
    virtual int size(Event*);
    virtual T* object(Event*, int);
    virtual void remove(Event*, int);
    virtual std::string directoryName();

    EfficiencyCounter<T> _efficiency;
    float _minPt, _maxPt, _minEta, _maxEta;

};

#endif // ifndef PoTATo_common_Condition_h
