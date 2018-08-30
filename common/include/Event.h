//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Event.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Event_h
#define PoTATo_common_Event_h

#include <vector>

#include "Jet.h"
#include "Lepton.h"
#include "MissingEt.h"
#include "ModeType.h"
#include "SampleType.h"
#include "Vector.h"

class Event {
public:
    Event() {};
    Event(Event&);
    virtual ~Event();

    Mode::Type mode() { return _mode; }
    Sample::Type sample() { return _sample; }
    unsigned int runNumber() { return _runNumber; }
    unsigned int lumiBlock() { return _lumiBlock; }
    unsigned int eventNumber() { return _eventNumber; }
    void trigger(unsigned int&, unsigned int&, unsigned int&, unsigned int&, unsigned int&);

    int nLeptons() { return _leptons->size(); }
    Lepton* lepton(int i) { return _leptons->at(i); }
    void removeLepton(int);
    void sortLeptons();

    int nJets() { return _jets->size(); }
    Jet* jet(int i) { return _jets->at(i); }
    void removeJet(int);
    void sortJets();

    MissingEt* missingEt() { return _met; }

    int nVertices() { return _n_vertices; }
    int nFirstVertices() { return _n_first_vertices; }

    double weightMENominal() { return _weight_me_nominal; }

    friend class EventReader;

protected:
    Mode::Type _mode;
    Sample::Type _sample;
    unsigned int _runNumber, _lumiBlock, _eventNumber;
    unsigned int _trigger_smu, _trigger_se, _trigger_mumu, _trigger_emu, _trigger_ee;
    std::vector<Lepton*>* _leptons = nullptr;
    std::vector<Jet*>* _jets = nullptr;
    MissingEt* _met = nullptr;
    int _n_vertices, _n_first_vertices;
    double _weight_me_nominal;

};

#endif // ifndef PoTATo_common_Event_h
