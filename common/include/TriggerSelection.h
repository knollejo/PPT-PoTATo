//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    TriggerSelection.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_TriggerSelection_h
#define PoTATo_common_TriggerSelection_h

#include <string>

#include "Action.h"
#include "Event.h"
#include "ModeType.h"
#include "Result.h"
#include "SampleType.h"

namespace TriggerMap {
    namespace SMu {
        const int HLT_IsoMu24 = 0x1;
        const int HLT_IsoMu27 = 0x2;
        const int HLT_IsoMu30 = 0x4;
        const int HLT_Mu45_eta2p1 = 0x8;
        const int HLT_Mu50 = 0x10;
        const int HLT_Mu55 = 0x20;
        const int HLT_TkMu50 = 0x40;
    }
    namespace SE {
        const int HLT_Ele27_WPTight_Gsf = 0x1;
        const int HLT_Ele32_WPTight_Gsf = 0x2;
        const int HLT_Ele35_WPTight_Gsf = 0x4;
        const int HLT_Ele38_WPTight_Gsf = 0x8;
        const int HLT_Ele40_WPTight_Gsf = 0x10;
        const int HLT_Ele105_CaloIdVT_GsfTrkIdT = 0x20;
        const int HLT_Ele115_CaloIdVT_GsfTrkIdT = 0x40;
        const int HLT_Photon200 = 0x80;
    }
    namespace MuMu {
        const int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = 0x1;
        const int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = 0x2;
        const int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 = 0x4;
        const int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = 0x8;
        const int HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8 = 0x10;
        const int HLT_TripleMu_10_5_5_DZ = 0x20;
        const int HLT_TripleMu_12_10_5 = 0x40;
        const int HLT_TripleMu_5_3_3_Mass3p8to60_DZ = 0x80;
    }
    namespace EMu {
        const int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = 0x1;
        const int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = 0x2;
        const int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = 0x4;
        const int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0x8;
        const int HLT_Mu8_DiEle12_CaloIdL_TrackIdL = 0x10;
        const int HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ = 0x20;
        const int HLT_DiMu9_Ele9_CaloIdL_TrackIdL = 0x40;
        const int HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ = 0x80;
        const int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = 0x100;
        const int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0x200;
        const int HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0x400;
    }
    namespace EE {
        const int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = 0x1;
        const int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0x2;
        const int HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = 0x4;
    }
}

class TriggerSelection : public Action {
public:
    TriggerSelection(bool cutmc) : _modesToRun(0), _cutMonteCarlo(cutmc) {}
    virtual void initialize(Result*);
    virtual float execute(Event*);
    virtual void finalize(bool) {}
    virtual std::string getName() = 0;

    virtual Mode::Type checkTriggers(Sample::Type, Mode::Type, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int) = 0;
    Mode::Type getTriggeredModes() { return _triggeredModes; }
    void setDatasets(Mode::Type modes) { _modesToRun = modes; }

protected:
    Mode::Type _modesToRun, _triggeredModes;
    int _sampleid, _modeid;
    unsigned int _smu, _se, _mumu, _emu, _ee;
    bool _cutMonteCarlo;

};

#endif // ifndef PoTATo_common_TriggerSelection_h
