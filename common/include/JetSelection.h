//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    JetSelection.h
// Author:  Joscha Knolle
// Date:    2018-05-04
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_JetSelection_h
#define PoTATo_common_JetSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class JetSelection : public Action {
public:
    JetSelection(bool, bool, bool, bool, bool, bool, bool, bool, int, int, int, int, int, float*);
    virtual ~JetSelection();
    void initialize(Result*);
    float execute(Event*);
    void finalize(bool) {}
    std::string getName() { return "JetSelection"; }

protected:
    // Configuration
    bool _cutJets, _cutBtags, _storeNumber, _storePt, _storeEta, _storePhi, _storeBtags, _storeBtagDisc;
    int _minJets, _maxJets, _minBtags, _maxBtags, _nMinJetPt;
    float* _minJetPt;

    // Data fields
    bool _passedJets, _passedBtags;
    int _nJets, _nBtags;
    int* _btagIndex = nullptr;
    float* _ptJet = nullptr;
    float* _etaJet = nullptr;
    float* _phiJet = nullptr;
    float* _btagDisc = nullptr;

};

#endif // ifndef PoTATo_common_JetSelection_h
