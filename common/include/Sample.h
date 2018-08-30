//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Sample.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Sample_h
#define PoTATo_common_Sample_h

#include "SampleType.h"

namespace Sample {
    enum : Type {
        // 2017 samples
        Run2017A = 0x2,
        Run2017B = 0x4,
        Run2017C = 0x8,
        Run2017D = 0x10,
        Run2017E = 0x20,
        Run2017F = 0x40,
        MC2017   = 0x80,
    };
    const Type Run2017 = Run2017A | Run2017B | Run2017C | Run2017D | Run2017E | Run2017F;
    const Type Data = Run2017;
    const Type MonteCarlo = MC2017;
}

#endif // ifndef PoTATo_common_Sample_h
