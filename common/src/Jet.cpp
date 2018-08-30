//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Jet.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "Jet.h"

Jet::Jet(
    LorentzVector lv,
    double btagdisc,
    double pileupdisc,
    int pileupflag
):
    Vector(lv),
    _btagDisc(btagdisc),
    _pileupJetId(pileupdisc),
    _pileupJetIdFlag(pileupflag),
    _isBtagged(false),
    _isFromPileup(false)
{}
