//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MinDistancePreselection.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_MinDistancePreselection_h
#define PoTATo_common_MinDistancePreselection_h

#include "Action.h"
#include "EfficiencyCounter.h"
#include "Event.h"
#include "Result.h"
#include "Vector.h"

template <typename T> class MinDistancePreselection : public Action {
public:
    MinDistancePreselection(double mind) : _mindistance(mind) {}
    virtual void initialize(Result*) {}
    virtual float execute(Event*);
    virtual void finalize(bool writeFile) { if(writeFile) _efficiency.write(getName()); }

protected:
    virtual void setup(Event*) = 0;
    virtual int nProbes() = 0;
    virtual int nRefs(int) = 0;
    virtual Vector* getProbe(int) = 0;
    virtual Vector* getRef(int, int) = 0;
    virtual void removeProbe(int) = 0;

    EfficiencyCounter<T> _efficiency;
    float _mindistance;

};

#endif // ifndef TTZ_MinDistancePreselection_h
