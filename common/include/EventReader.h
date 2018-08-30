//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EventReader.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_EventReader_h
#define PoTATo_common_EventReader_h

#include <string>
#include <vector>

#include <TTree.h>

#include "Event.h"
#include "LorentzVector.h"
#include "ModeType.h"
#include "SampleType.h"

class EventReader {
public:
    virtual ~EventReader();
    int setTree(TTree*, Mode::Type, Sample::Type);
    Event* readLocalEntry(int);
    std::string getFilename();

protected:
    TTree* _tree;
    Mode::Type _mode;
    Sample::Type _sample;

    unsigned int _runNumber, _lumiBlock, _eventNumber;

    unsigned int _triggerBitsSMu, _triggerBitsSE, _triggerBitsMuMu, _triggerBitsEMu, _triggerBitsEE;

    std::vector<LorentzVector::TreeClass>* _leptons = nullptr;
    std::vector<int>* _lepPdgId = nullptr;
    std::vector<int>* _lepLooseId = nullptr;
    std::vector<int>* _lepMediumId = nullptr;
    std::vector<int>* _lepTightId = nullptr;
    std::vector<double>* _lepPfIso = nullptr;
    std::vector<double>* _lepMiniIsoCh = nullptr;
    std::vector<double>* _lepMiniIsoNeu = nullptr;

    std::vector<LorentzVector::TreeClass>* _jets = nullptr;
    std::vector<double>* _jetPileupIdFull = nullptr;
    std::vector<int>* _jetPileupIdFlagFull = nullptr;
    std::vector<double>* _jetBTagDeepCSV = nullptr;

    LorentzVector::TreeClass* _met = nullptr;

    int _vertMulti, _firstVertMulti;
    double _weightMENominal;

    bool isNullVector(LorentzVector::TreeClass);
    void clearPointers();

};


#endif // ifndef PoTATo_common_Event_h
