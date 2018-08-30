//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Action.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Action_h
#define PoTATo_common_Action_h

#include <string>

#include "Event.h"
#include "Result.h"

class Action {
public:
    virtual ~Action() {}
    virtual void initialize(Result*) = 0;
    virtual float execute(Event*) = 0;
    virtual void finalize(bool) = 0;
    virtual std::string getName() = 0;

protected:

};

#endif // ifndef PoTATo_common_Action_h
