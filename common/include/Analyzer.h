//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Analyzer.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Analyzer_h
#define PoTATo_common_Analyzer_h

#include <string>
#include <vector>

#include <TFile.h>
#include <TTree.h>

#include "Action.h"
#include "EventReader.h"
#include "ModeType.h"
#include "Result.h"
#include "SampleType.h"

class Analyzer {
public:
    Analyzer();
    virtual ~Analyzer();

    virtual void initialize();
    virtual void processTree(TTree*, Mode::Type, Sample::Type, double, double, int, int);
    virtual void finalize();

    void setOutput(std::string);
    void registerAction(Action* action) { _actions->push_back(action); };
    TTree* getResult() { return _result->tree(); }

protected:
    EventReader _reader;

    std::string _filename;
    TFile* _file;
    bool _writeFile;

    float _lumifactor, _eventweight;

    std::vector<Action*>* _actions;
    int _nTrees, _nProcessedEvents, _nPassedEvents;
    int* _cutflow = nullptr;

    Result* _result = nullptr;
    unsigned int _runNumber, _lumiBlock, _eventNumber;

};

#endif // ifndef PoTATo_common_Analyzer_h
