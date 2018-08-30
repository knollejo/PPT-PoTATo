//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EventReader.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include <TFile.h>

#include "EventReader.h"
#include "Jet.h"
#include "Lepton.h"
#include "MissingEt.h"
#include "Mode.h"

EventReader::~EventReader() {
    clearPointers();
}

int EventReader::setTree(TTree* tree, Mode::Type mode, Sample::Type sample) {
    _tree = tree;
    _mode = mode;
    _sample = sample;

    clearPointers();

    _tree->SetBranchAddress("runNumber", &_runNumber);
    _tree->SetBranchAddress("lumiBlock", &_lumiBlock);
    _tree->SetBranchAddress("eventNumber", &_eventNumber);

    _tree->SetBranchAddress("triggerBitsSMu", &_triggerBitsSMu);
    _tree->SetBranchAddress("triggerBitsSE", &_triggerBitsSE);
    _tree->SetBranchAddress("triggerBitsMuMu", &_triggerBitsMuMu);
    _tree->SetBranchAddress("triggerBitsEMu", &_triggerBitsEMu);
    _tree->SetBranchAddress("triggerBitsEE", &_triggerBitsEE);

    _tree->SetBranchAddress("lepPdgId", &_lepPdgId);
    _tree->SetBranchAddress("leptons", &_leptons);
    _tree->SetBranchAddress("lepLooseId", &_lepLooseId);
    _tree->SetBranchAddress("lepMediumId", &_lepMediumId);
    _tree->SetBranchAddress("lepTightId", &_lepTightId);
    _tree->SetBranchAddress("lepPfIso", &_lepPfIso);
    _tree->SetBranchAddress("lepMiniIsoCh", &_lepMiniIsoCh);
    _tree->SetBranchAddress("lepMiniIsoNeu", &_lepMiniIsoNeu);

    _tree->SetBranchAddress("jets", &_jets);
    _tree->SetBranchAddress("jetPileupIdFull", &_jetPileupIdFull);
    _tree->SetBranchAddress("jetPileupIdFlagFull", &_jetPileupIdFlagFull);
    _tree->SetBranchAddress("jetBTagDeepCSV", &_jetBTagDeepCSV);

    _tree->SetBranchAddress("met", &_met);

    _tree->SetBranchAddress("vertMulti", &_vertMulti);
    _tree->SetBranchAddress("firstVertMulti", &_firstVertMulti);

    if((mode&Mode::MonteCarlo)!=0) {
        _tree->SetBranchAddress("weightMENominal", &_weightMENominal);
    }
    
    return tree->GetEntries();
}

Event* EventReader::readLocalEntry(int entry) {
    _tree->GetEntry(entry);
    Event* ev = new Event;

    // Mode, sample
    ev->_mode = _mode;
    ev->_sample = _sample;

    // Event number
    ev->_runNumber = _runNumber;
    ev->_lumiBlock = _lumiBlock;
    ev->_eventNumber = _eventNumber;

    // Triggers
    ev->_trigger_smu = _triggerBitsSMu;
    ev->_trigger_se = _triggerBitsSE;
    ev->_trigger_mumu = _triggerBitsMuMu;
    ev->_trigger_emu = _triggerBitsEMu;
    ev->_trigger_ee = _triggerBitsEE;

    // Vertices
    ev->_n_vertices = _vertMulti;
    ev->_n_first_vertices = _firstVertMulti;

    // Leptons
    int nLeptons = _leptons->size();
    ev->_leptons = new std::vector<Lepton*>;
    ev->_leptons->reserve(nLeptons);
    for(int i=0; i<nLeptons; i++) ev->_leptons->push_back(new Lepton(
        LorentzVector(_leptons->at(i)), _lepPdgId->at(i),
        _lepLooseId->at(i)>0, _lepMediumId->at(i)>0, _lepTightId->at(i)>0,
        _lepPfIso->at(i), _lepMiniIsoCh->at(i)+_lepMiniIsoNeu->at(i)
    ));
    ev->_leptons->shrink_to_fit();
    ev->sortLeptons();

    // Jets
    int nJets = _jets->size();
    ev->_jets = new std::vector<Jet*>;
    ev->_jets->reserve(nJets);
    for(int i=0; i<nJets; i++) ev->_jets->push_back(new Jet(
        LorentzVector(_jets->at(i)), _jetBTagDeepCSV->at(i),
        _jetPileupIdFull->at(i), _jetPileupIdFlagFull->at(i)
    ));
    ev->_jets->shrink_to_fit();
    ev->sortJets();

    // Missing energy
    ev->_met = new MissingEt(*_met);

    // true vertices, event generator weights
    ev->_weight_me_nominal = (_mode&Mode::MonteCarlo)!=0 ? _weightMENominal : 1.0;

    return ev;
}

std::string EventReader::getFilename() {
    TFile* file = _tree->GetCurrentFile();
    if(file) {
        std::string name = file->GetName();
        return name.substr(name.find_last_of('/')+1);
    } else return "";
}

bool EventReader::isNullVector(LorentzVector::TreeClass lv) {
    return lv.M()==0.0 && lv.Pt()==0.0 && lv.Eta()==0.0 && lv.Phi()==0.0;
}

#define CLEAR_POINTER(NAME) if(NAME!=nullptr) { delete NAME; NAME = nullptr; }
void EventReader::clearPointers() {
    CLEAR_POINTER(_lepPdgId)
    CLEAR_POINTER(_leptons)
    CLEAR_POINTER(_lepLooseId)
    CLEAR_POINTER(_lepMediumId)
    CLEAR_POINTER(_lepTightId)
    CLEAR_POINTER(_lepPfIso)
    CLEAR_POINTER(_lepMiniIsoCh)
    CLEAR_POINTER(_lepMiniIsoNeu)
    CLEAR_POINTER(_jets)
    CLEAR_POINTER(_jetPileupIdFull)
    CLEAR_POINTER(_jetPileupIdFlagFull)
    CLEAR_POINTER(_jetBTagDeepCSV)
    CLEAR_POINTER(_met)
}
#undef CLEAR_POINTER
