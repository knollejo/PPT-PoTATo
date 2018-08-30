//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    FirstVertexSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "FirstVertexSelection.h"

void FirstVertexSelection::initialize(Result* res) {
    if(!_cutFirstVertices) res->branch("passedFirstVertices", &_passedFirstVertices);
}

float FirstVertexSelection::execute(Event* ev) {
    _passedFirstVertices = ev->nFirstVertices()>0;
    if(_cutFirstVertices && !_passedFirstVertices) return 0.0;
    return 1.0;
}
