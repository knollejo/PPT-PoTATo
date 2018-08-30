//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MissingEtSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "MissingEtSelection.h"

MissingEtSelection::MissingEtSelection(
    bool cutmet,
    double minmet,
    double maxmet
) :
    _cutMissingEt(cutmet),
    _minMet(minmet),
    _maxMet(maxmet)
{
}

void MissingEtSelection::initialize(Result* res) {
    res->branch("missingEt", &_met);
    if(!_cutMissingEt) res->branch("passedMissingEt", &_passedMissingEt);
}

float MissingEtSelection::execute(Event* ev) {
    // MET cuts
    _met = ev->missingEt()->Et();
    _passedMissingEt = (_minMet<0.0 || _met>_minMet) && (_maxMet<0.0 || _met<_maxMet);
    if(_cutMissingEt && !_passedMissingEt) return 0.0;

    return 1.0;
}
