//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Jet.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Jet_h
#define PoTATo_common_Jet_h

#include <string>

#include "LorentzVector.h"
#include "Vector.h"

class Jet : public Vector {
public:
    Jet(LorentzVector, double, double, int);
    virtual std::string getType() { return "jet"; }

    bool isBtagged() { return _isBtagged; }
    bool isFromPileup() { return _isFromPileup; }

    double btagDiscriminant() { return _btagDisc; }
    double pileupDiscriminant() { return _pileupJetId; }
    int pileupFlag() { return _pileupJetIdFlag; }

    friend class JetCondition;

protected:
    double _btagDisc, _pileupJetId;
    int _pileupJetIdFlag;
    bool _isBtagged, _isFromPileup;

};


#endif // ifndef PoTATo_common_Jet_h
