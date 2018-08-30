//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: trileptonic
// File:    TrileptonTrigger.h
// Author:  Joscha Knolle
// Date:    2018-05-07
//----------------------------------------------------------------------------//

#ifndef PoTATo_trileptonic_TrileptonTrigger_h
#define PoTATo_trileptonic_TrileptonTrigger_h

#include <string>

#include "ModeType.h"
#include "TriggerSelection.h"
#include "Result.h"
#include "SampleType.h"

class TrileptonTrigger : public TriggerSelection {
public:
    TrileptonTrigger(bool cutmc) : TriggerSelection(cutmc) {}
    void initialize(Result*);
    std::string getName() { return "TrileptonTrigger"; }

    Mode::Type checkTriggers(Sample::Type, Mode::Type, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

protected:
    bool _triggeredSingleMuon, _triggeredSingleElectron, _triggeredDoubleMuon,
         _triggeredDoubleElectron, _triggeredElectronMuon;

};

#endif // ifndef PoTATo_trileptonic_TrileptonTrigger_h
