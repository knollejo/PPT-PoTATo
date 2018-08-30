//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    LeptonSelection.h
// Author:  Joscha Knolle
// Date:    2018-05-04
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_LeptonSelection_h
#define PoTATo_common_LeptonSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "Result.h"

class LeptonSelection : public Action {
public:
    LeptonSelection(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, int, int, int, float*);
    virtual ~LeptonSelection();
    void initialize(Result*);
    float execute(Event*);
    void finalize(bool) {}
    std::string getName();

protected:
    // Configuration
    bool _cutLeptons, _onlyMuons, _onlyElectrons, _storeNumber, _storePdgId,_storePt,
         _storeEta, _storePhi, _storeRelIso, _storeMiniIso;
    int _minLeptons, _maxLeptons, _nMinLepPt;
    float* _minLepPt;

    // Data fields
    bool _passedLeptons;
    int _nLep;
    int* _pdgLep = nullptr;
    float* _ptLep = nullptr;
    float* _etaLep = nullptr;
    float* _phiLep = nullptr;
    float* _isoLep = nullptr;
    float* _miniIsoLep = nullptr;

};

#endif // ifndef PoTATo_common_LeptonSelection_h
