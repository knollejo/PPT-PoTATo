//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    JetSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-05-04
//----------------------------------------------------------------------------//

#include <algorithm>

#include "JetSelection.h"

JetSelection::JetSelection(
    bool cutjets,
    bool cutbtags,
    bool storenum,
    bool storept,
    bool storeeta,
    bool storephi,
    bool storebtag,
    bool storebdisc,
    int minjets,
    int maxjets,
    int minbtags,
    int maxbtags,
    int nminjetpt,
    float* minjetpt
) :
    _cutJets(cutjets), _cutBtags(cutbtags), _storeNumber(storenum), _storePt(storept),
    _storeEta(storeeta), _storePhi(storephi), _storeBtags(storebtag), _storeBtagDisc(storebdisc),
    _minJets(minjets), _maxJets(maxjets), _minBtags(minbtags), _maxBtags(maxbtags),
    _nMinJetPt(nminjetpt), _minJetPt(minjetpt)
{
    if(_storeNumber) {
        _ptJet = new float[10];
        _etaJet = new float[10];
        _phiJet = new float[10];
        _btagDisc = new float[10];
        if(_storeBtags) _btagIndex = new int[10];
    }
}

JetSelection::~JetSelection() {
    if(_minJetPt!=nullptr) delete [] _minJetPt;
    if(_ptJet!=nullptr) delete [] _ptJet;
    if(_etaJet!=nullptr) delete [] _etaJet;
    if(_phiJet!=nullptr) delete [] _phiJet;
    if(_btagIndex!=nullptr) delete [] _btagIndex;
    if(_btagDisc!=nullptr) delete [] _btagDisc;
}

void JetSelection::initialize(Result* res) {
    if(_storeNumber) {
        res->branch("nJets", &_nJets);
        if(_storePt) res->branch("jetPt", _ptJet, "nJets");
        if(_storeEta) res->branch("jetEta", _etaJet, "nJets");
        if(_storePhi) res->branch("jetPhi", _phiJet, "nJets");
        if(_storeBtagDisc) res->branch("btagDisc", _btagDisc, "nJets");

        if(_storeBtags) {
            res->branch("nBtags", &_nBtags);
            res->branch("btaggedJets", _btagIndex, "nBtags");
        }
    }
    if(!_cutJets) res->branch("passedNJets", &_passedJets);
    if(!_cutBtags) res->branch("passedNBtags", &_passedBtags);
}

float JetSelection::execute(Event* ev) {
    // require a number of jets
    _nJets = ev->nJets();
    if(_nMinJetPt>0) for(int i=0; i<std::min(_nJets, _nMinJetPt); i++)
        if(ev->jet(i)->Pt()<_minJetPt[i]) {
            _nJets = i;
            break;
        }
    _passedJets = (_minJets<0 || _nJets>=_minJets) && (_maxJets<0 || _nJets<=_maxJets);
    if(_cutJets && !_passedJets)
        return 0.0;

    // require a number of b-tagged jets
    _nBtags = 0;
    for(int i=0; i<_nJets; i++) if(ev->jet(i)->isBtagged()) {
        if(_storeNumber && _storeBtags) _btagIndex[_nBtags] = i;
        _nBtags++;
    }
    _passedBtags = (_minBtags<0 || _nBtags>=_minBtags) && (_maxBtags<0 || _nBtags<=_maxBtags);
    if(_cutBtags && !_passedBtags)
        return 0.0;

    // store jet properties
    if(_storeNumber && (_storePt || _storeEta || _storePhi || _storeBtagDisc))
        for(int i=0; i<std::min(_nJets, 10); i++) {
            _ptJet[i] = ev->jet(i)->Pt();
            _etaJet[i] = ev->jet(i)->Eta();
            _phiJet[i] = ev->jet(i)->Phi();
            _btagDisc[i] = ev->jet(i)->btagDiscriminant();
        }

    return 1.0;
}
