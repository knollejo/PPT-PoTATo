//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Lepton.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Lepton_h
#define PoTATo_common_Lepton_h

#include <string>

#include "LorentzVector.h"
#include "Vector.h"

class Lepton : public Vector {
public:
    enum {
        ELECTRON_PDG = 11,
        MUON_PDG = 13,
    };

    Lepton(LorentzVector, int, bool, bool, bool, double, double);
    virtual std::string getType();

    int pdgId() { return _pdgId; }
    bool isElectron();
    bool isMuon();

    bool hasLooseId() { return _idLoose; }
    bool hasMediumId() { return _idMedium; }
    bool hasTightId() { return _idTight; }

    double relIso() { return _pfIso; }
    double miniIso() { return _miniIso; }

protected:
    int _pdgId;
    bool _idLoose, _idMedium, _idTight;
    double _pfIso, _miniIso;

};

#endif // ifndef PoTATo_common_Lepton_h
