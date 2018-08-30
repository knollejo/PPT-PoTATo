//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Wboson.h
// Author:  Joscha Knolle
// Date:    2018-04-23
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Wboson_h
#define PoTATo_common_Wboson_h

#include "Lepton.h"
#include "LorentzVector.h"
#include "Vector.h"

class Wboson : public Vector {
public:
    Wboson(LorentzVector, int, Lepton*, Vector*);
    ~Wboson();
    virtual std::string getType() { return "Wboson"; }

    int decayMode() { return _decayMode; }
    Lepton* lepton() { return _lepton; }
    Vector* neutrino() { return _neutrino; }

protected:
    int _decayMode;
    Lepton* _lepton = nullptr;
    Vector* _neutrino = nullptr;

};

#endif // ifndef TTZ_Wboson_h
