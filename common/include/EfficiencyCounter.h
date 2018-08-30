//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EfficiencyCounter.h
// Author:  Joscha Knolle
// Date:    2018-05-08
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_EfficiencyCounter_h
#define PoTATo_common_EfficiencyCounter_h

#include <string>

template <typename T> class EfficiencyCounter {
public:
    EfficiencyCounter();
    virtual void pass() { _passedObjects++; }
    virtual void fail() { _failedObjects++; }
    virtual void write(std::string);

protected:
    virtual std::string directoryName();
    int _passedObjects, _failedObjects, _counter;

};

#endif // ifndef PoTATo_common_EfficiencyCounter_h
