//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    RenameAction.h
// Author:  Joscha Knolle
// Date:    2018-05-02
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_RenameAction_h
#define PoTATo_common_RenameAction_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class RenameAction : public Action {
public:
    RenameAction(Action* a, std::string n) : _action(a), _name(n) {}
    virtual ~RenameAction() { delete _action; }
    virtual void initialize(Result* res) { _action->initialize(res); }
    virtual float execute(Event* ev) { return _action->execute(ev); }
    virtual void finalize(bool writeFile) { _action->finalize(writeFile); }
    virtual std::string getName() { return _name; }

protected:
    Action* _action;
    std::string _name;

};

#endif // ifndef PoTATo_common_RenameAction_h
