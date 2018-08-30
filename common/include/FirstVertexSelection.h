//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    FirstVertexSelection.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_FirstVertexSelection_h
#define PoTATo_common_FirstVertexSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class FirstVertexSelection : public Action {
public:
    FirstVertexSelection(bool cutFV) : _cutFirstVertices(cutFV) {}
    void initialize(Result*);
    float execute(Event*);
    void finalize(bool) {}
    std::string getName() { return "FirstVertexSelection"; }

protected:
    bool _cutFirstVertices, _passedFirstVertices;

};

#endif // ifndef PoTATo_common_FirstVertexSelection_h
