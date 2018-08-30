//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Mode.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Mode_h
#define PoTATo_common_Mode_h

#include "ModeType.h"

namespace Mode {
    enum : Type {
        // Data modes
        SingleElectron = 0x2,
        SingleMuon     = 0x4,
        DoubleElectron = 0x8,
        DoubleMuon     = 0x10,
        ElectronMuon   = 0x20,

        // Monte Carlo modes
        TTbarZtoLLNuNu  = 0x40,
        TTbarWJetstoLNu = 0x80,
        TTbarHtononBB   = 0x100,
        TTbarGJets      = 0x200,
        TTbarDilepton   = 0x400,
        DYJetsToLL      = 0x800,
        WJetsToLNu      = 0x1000,
        ZZto4L          = 0x2000,
        WZto3L          = 0x4000,
        ZGto2LG         = 0x8000,
        WGtoLNuG        = 0x10000,
        ZZZtoAll        = 0x20000,
        WZZtoAll        = 0x40000,
        WWZtoAll        = 0x80000,
        FourTops        = 0x100000,
        TZQtoLL         = 0x200000,
        SingleTopWLL    = 0x400000,
    };
    const Type SingleLepton = SingleElectron | SingleMuon;
    const Type DoubleLepton = DoubleElectron | DoubleMuon | ElectronMuon;
    const Type Data         = SingleLepton | DoubleLepton;
    const Type SingleBoson  = DYJetsToLL | WJetsToLNu;
    const Type Diboson      = ZZto4L | WZto3L | ZGto2LG | WGtoLNuG;
    const Type Triboson     = ZZZtoAll | WZZtoAll | WWZtoAll;
    const Type TTbarX       = TTbarZtoLLNuNu | TTbarWJetstoLNu | TTbarHtononBB | TTbarGJets | TTbarDilepton;
    const Type TopMC        = TTbarX | FourTops | TZQtoLL | SingleTopWLL;
    const Type MonteCarlo   = SingleBoson | Diboson | Triboson | TopMC;
}

#endif // ifndef PoTATo_common_Mode_h
