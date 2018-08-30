//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MissingEt.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_MissingEt_h
#define PoTATo_common_MissingEt_h

#include <string>

#include "LorentzVector.h"
#include "Vector.h"

class MissingEt : public Vector {
public:
    MissingEt(LorentzVector);
    virtual std::string getType() { return "met"; }

protected:

};

#endif // ifndef PoTATo_common_MissingEt_h
