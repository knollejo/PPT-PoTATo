//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    LeptonCondition.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_LeptonCondition_h
#define PoTATo_common_LeptonCondition_h

#include <string>

#include "Condition.h"
#include "Lepton.h"

class LeptonCondition : public Condition<Lepton> {
public:
    LeptonCondition(float, float, float, float, bool, bool, bool, bool, bool, bool, bool, bool, float, float, float, float);
    virtual ~LeptonCondition() {}
    virtual std::string getName();

    virtual bool check(Lepton*);

protected:
    bool _cutElectrons, _cutMuons,
         _requireLooseId, _invertLooseId,
         _requireMediumId, _invertMediumId,
         _requireTightId, _invertTightId;
    float _minIso, _maxIso, _minMiniIso, _maxMiniIso;

};

#endif // ifndef PoTATo_common_LeptonCondition_h
