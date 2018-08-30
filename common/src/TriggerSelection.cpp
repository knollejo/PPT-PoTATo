//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    TriggerSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "Sample.h"
#include "TriggerSelection.h"

void TriggerSelection::initialize(Result* res) {
    res->branch("sampleid", &_sampleid);
    res->branch("modeid", &_modeid);
}

float TriggerSelection::execute(Event* ev) {
    _sampleid = ev->sample();
    _modeid = ev->mode();
    if((_modeid&_modesToRun)==0)
        return 0.0;
    ev->trigger(_smu, _se, _mumu, _emu, _ee);
    _triggeredModes = checkTriggers(_sampleid, _modeid, _smu, _se, _mumu, _emu, _ee);
    return 1.0*(_triggeredModes!=0 || (!_cutMonteCarlo && (_sampleid&Sample::MonteCarlo)!=0));
}
