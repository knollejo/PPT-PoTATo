//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    ZCandidateSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-05-07
//----------------------------------------------------------------------------//


#include <TMath.h>

#include "LorentzVector.h"
#include "ZCandidateSelection.h"

ZCandidateSelection::ZCandidateSelection(
    bool cutCand, float minMass, float zMass
) :
    cutCandidate(cutCand), minMassDiff(minMass), trueZmass(zMass)
{
}

void ZCandidateSelection::initialize(Result* res) {
    res->branch("positiveZLepton", &positive);
    res->branch("negativeZLepton", &negative);
    res->branch("dileptonMass", &massDilep);
    res->branch("dileptonPt", &ptDilep);
    res->branch("dileptonEta", &etaDilep);
    res->branch("dileptonPhi", &phiDilep);
    res->branch("dileptonDeltaPhi", &deltaPhiDilep);
    if(!cutCandidate)
        res->branch("passedZCandidate", &passedZCandidate);
}

float ZCandidateSelection::execute(Event* ev) {
    // require OSSF lepton pair with mass close to Z mass
    positive = -1;
    negative = -1;
    double massdiff = minMassDiff, mass;
    for(int first=0; first<ev->nLeptons(); first++) {
        if(ev->lepton(first)->pdgId()<0)
            continue;
        for(int second=0; second<ev->nLeptons(); second++) {
            if(first==second || ev->lepton(first)->pdgId()!=-ev->lepton(second)->pdgId())
                continue;
            LorentzVector dilep = (*ev->lepton(first)->Vec())+(*ev->lepton(second)->Vec());
            mass = dilep.M();
            if(TMath::Abs(mass-trueZmass)<massdiff) {
                positive = first;
                negative = second;
                massdiff = TMath::Abs(mass-trueZmass);
                massDilep = mass;
                ptDilep = dilep.Pt();
                etaDilep = dilep.Eta();
                phiDilep = dilep.Phi();
                deltaPhiDilep = ev->lepton(first)->DeltaPhi(*ev->lepton(second));
            }
        }
    }
    passedZCandidate = bool(positive>=0);
    if(passedZCandidate)
        return 1.0;
    else {
        massDilep = -1.0;
        ptDilep = -1.0;
        etaDilep = 0.0;
        phiDilep = 0.0;
        deltaPhiDilep = -1.0;
        return 1.0*(!cutCandidate);
    }
}

void ZCandidateSelection::selectedLeptons(int& pos, int& neg) {
    pos = positive;
    neg = negative;
}
