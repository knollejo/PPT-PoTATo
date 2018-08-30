//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    LorentzVector.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_LorentzVector_h
#define PoTATo_common_LorentzVector_h

#include <Math/GenVector/PtEtaPhiM4D.h>
#include <Math/GenVector/LorentzVector.h>
#include <TLorentzVector.h>

class LorentzVector : public TLorentzVector {
public:
    typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> TreeClass;

    LorentzVector() : TLorentzVector() {}
    LorentzVector(const TreeClass & other) : TLorentzVector(other.X(), other.Y(), other.Z(), other.T()) {}
    LorentzVector(const TLorentzVector & other) : TLorentzVector(other) {}
    LorentzVector(const LorentzVector & other) : TLorentzVector(other.X(), other.Y(), other.Z(), other.T()) {}

protected:

};

#endif // ifndef PoTATo_common_LorentzVector_h
