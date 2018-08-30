//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    JetCondition.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "JetCondition.h"

JetCondition::JetCondition(
    float minpt,
    float maxpt,
    float mineta,
    float maxeta,
    bool cutpileup,
    bool invertpileup,
    int pileupwp,
    float btagwp,
    float minbtag,
    float maxbtag
):
    Condition<Jet>(minpt, maxpt, mineta, maxeta),
    _cutPileup(cutpileup),
    _invertPileup(invertpileup),
    _pileupWP(pileupwp),
    _btagWP(btagwp),
    _minBtag(minbtag),
    _maxBtag(maxbtag)
{}

bool JetCondition::check(Jet* jet) {
    if(!Condition<Jet>::check(jet)) return false;

    // Evaluate b-tagging, pileup ID
    if(_btagWP>-1.0) jet->_isBtagged = bool(jet->btagDiscriminant()>_btagWP);
    if(_pileupWP>0) jet->_isFromPileup = bool((jet->pileupFlag()&_pileupWP)==0);

    // Apply cuts
    if(_cutPileup && _invertPileup!=jet->isFromPileup()) return false;
    if((_minBtag>-1.0 && jet->btagDiscriminant()<_minBtag) || (_maxBtag>-1.0 && jet->btagDiscriminant()>_maxBtag)) return false;

    return true;
}
