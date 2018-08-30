//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Vector.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Vector_h
#define PoTATo_common_Vector_h

#include <string>

#include "LorentzVector.h"

class Vector : public LorentzVector {
public:
    Vector(LorentzVector lv) : LorentzVector(lv) {}
    virtual std::string getType() { return "vector"; }
    LorentzVector* Vec() { return (LorentzVector*)this; }

    static bool ptOrder(Vector* vec1, Vector* vec2) { return vec1->Pt()>vec2->Pt(); }

protected:

};

#endif // ifndef PoTATo_common_Vector_h
