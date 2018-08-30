//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    LeptonSelection.cpp
// Author:  Joscha Knolle
// Date:    2018-05-04
//----------------------------------------------------------------------------//

#include <algorithm>
#include <cctype>

#include "LeptonSelection.h"

LeptonSelection::LeptonSelection(
    bool cutlep,
    bool onlymuon,
    bool onlyelec,
    bool storenum,
    bool storepdg,
    bool storept,
    bool storeeta,
    bool storephi,
    bool storeiso,
    bool storeminiiso,
    int minlep,
    int maxlep,
    int nminleppt,
    float* minleppt
):
    _cutLeptons(cutlep), _onlyMuons(onlymuon), _onlyElectrons(onlyelec), _storeNumber(storenum),
    _storePdgId(storepdg), _storePt(storept), _storeEta(storeeta), _storePhi(storephi),
    _storeRelIso(storeiso), _storeMiniIso(storeminiiso), _minLeptons(minlep), _maxLeptons(maxlep),
    _nMinLepPt(nminleppt), _minLepPt(minleppt)
{
    if(_storeNumber) {
        _pdgLep = new int[10];
        _ptLep = new float[10];
        _etaLep = new float[10];
        _phiLep = new float[10];
        _isoLep = new float[10];
        _miniIsoLep = new float[10];
    }
}

LeptonSelection::~LeptonSelection() {
    if(_pdgLep!=nullptr) delete [] _pdgLep;
    if(_ptLep!=nullptr) delete [] _ptLep;
    if(_etaLep!=nullptr) delete [] _etaLep;
    if(_phiLep!=nullptr) delete [] _phiLep;
    if(_isoLep!=nullptr) delete [] _isoLep;
    if(_miniIsoLep!=nullptr) delete [] _miniIsoLep;
}

void LeptonSelection::initialize(Result* res) {
    std::string prefix;
    if(_onlyMuons) prefix = "muon";
    else if(_onlyElectrons) prefix = "electron";
    else prefix = "lepton";

    if(_storeNumber) {
        std::string number = "n"+std::string(1, toupper(prefix[0]))+prefix.substr(1)+"s";
        res->branch(number, &_nLep);
        if(_storePdgId) res->branch(prefix+"PdgId", _pdgLep, number);
        if(_storePt) res->branch(prefix+"Pt", _ptLep, number);
        if(_storeEta) res->branch(prefix+"Eta", _etaLep, number);
        if(_storePhi) res->branch(prefix+"Phi", _phiLep, number);
        if(_storeRelIso) res->branch(prefix+"RelIso", _isoLep, number);
        if(_storeMiniIso) res->branch(prefix+"MiniIso", _miniIsoLep, number);
    }

    if(!_cutLeptons) res->branch("passedN"+std::string(1, toupper(prefix[0]))+prefix.substr(1)+"s", &_passedLeptons);
}

float LeptonSelection::execute(Event* ev) {
    // make list of indices
    int* indices = new int[ev->nLeptons()];
    _nLep = 0;
    for(int i=0; i<ev->nLeptons(); i++) {
        if((_onlyMuons && ev->lepton(i)->isMuon()) || (_onlyElectrons && ev->lepton(i)->isElectron()) || (!_onlyMuons && !_onlyElectrons)) {
            indices[_nLep] = i;
            _nLep++;
        }
    }

    // require a number of leptons
    if(_nMinLepPt>0) for(int i=0; i<std::min(_nLep, _nMinLepPt); i++)
        if(ev->lepton(indices[i])->Pt()<_minLepPt[i]) {
            _nLep = i;
            break;
        }
    _passedLeptons = (_minLeptons<0 || _nLep>=_minLeptons) && (_maxLeptons<0 || _nLep<=_maxLeptons);
    if(_cutLeptons && !_passedLeptons)
        return 0.0;

    // store lepton properties
    if(_storeNumber && (_storePdgId || _storePt || _storeEta || _storePhi || _storeRelIso || _storeMiniIso))
        for(int i=0; i<std::min(_nLep, 10); i++) {
            _pdgLep[i] = ev->lepton(indices[i])->pdgId();
            _ptLep[i] = ev->lepton(indices[i])->Pt();
            _etaLep[i] = ev->lepton(indices[i])->Eta();
            _phiLep[i] = ev->lepton(indices[i])->Phi();
            _isoLep[i] = ev->lepton(indices[i])->relIso();
            _miniIsoLep[i] = ev->lepton(indices[i])->miniIso();
        }

    return 1.0;
}

std::string LeptonSelection::getName() {
    if(_onlyMuons) return "MuonSelection";
    else if(_onlyElectrons) return "ElectronSelection";
    else return "LeptonSelection";
}
