//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Analyzer.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "Analyzer.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <TDirectory.h>
#include <TParameter.h>

#include "Event.h"

Analyzer::Analyzer() :
    _nTrees(0), _writeFile(false)
{
    _actions = new std::vector<Action*>;
}

Analyzer::~Analyzer() {
    for(std::vector<Action*>::iterator action=_actions->begin(); action!=_actions->end(); ++action) {
        if(!*action) delete (*action);
    }
    delete _actions;
    if(_cutflow!=nullptr) delete _cutflow;
    if(_result!=nullptr) delete _result;
}

void Analyzer::initialize() {
    if(_writeFile) _file = TFile::Open(_filename.c_str(), "RECREATE");
    _result = new Result();
    _result->branch("runNumber", &_runNumber);
    _result->branch("lumiBlock", &_lumiBlock);
    _result->branch("eventNumber", &_eventNumber);
    _result->branch("weight", &_eventweight);
    _result->branch("lumifactor", &_lumifactor);
    for(std::vector<Action*>::iterator action=_actions->begin(); action!=_actions->end(); ++action)
        (*action)->initialize(_result);
    _cutflow = new int[_actions->size()+1];
    for(unsigned int i=0; i<_actions->size()+1; i++)
        _cutflow[i] = 0;
}

void Analyzer::processTree(
    TTree* tree, Mode::Type mode, Sample::Type sample, double xsec, double nevents,
    int first, int last
) {
    int nEntries = _reader.setTree(tree, mode, sample);
    if(xsec>0.0) {
        if(nevents<0.0) nevents = nEntries;
        _lumifactor = xsec/nevents;
    } else _lumifactor = -1.0;
    _nTrees++;
    _nProcessedEvents = 0;
    _nPassedEvents = 0;
    std::cout << _nTrees << ": Read file " << _reader.getFilename() << std::endl;
    if(first<0 or last<0) {
        first = 0;
        last = nEntries;
    } else {
        last = std::min(last, nEntries);
    }
    for(int entry=first; entry<last; entry++) {
        _nProcessedEvents++;
        _eventweight = 1.0;
        Event* ev = _reader.readLocalEntry(entry);
        _runNumber = ev->runNumber();
        _lumiBlock = ev->lumiBlock();
        _eventNumber = ev->eventNumber();
        _cutflow[0]++;
        int i = 0;
        for(std::vector<Action*>::iterator action=_actions->begin(); action!=_actions->end(); ++action) {
            i++;
            _eventweight *= (*action)->execute(ev);
            if(_eventweight==0.0) break;
            else _cutflow[i]++;
        }
        if(_eventweight!=0.0) {
            _result->fill();
            _nPassedEvents++;
        }
    }
    std::cout << _nTrees << ": Processed " << _nProcessedEvents << " events, "
              << _nPassedEvents << " events passed selection" << std::endl;
}

void Analyzer::finalize() {
    for(std::vector<Action*>::iterator action=_actions->begin(); action!=_actions->end(); ++action) {
        if(_writeFile) _file->cd();
        (*action)->finalize(_writeFile);
    }
    if(_writeFile) {
        if(_writeFile) _file->cd();
        _result->tree()->Write();
        TDirectory* dir = _file->mkdir("cutflow", "Cutflow");
        dir->cd();
        for(unsigned int i=0; i<_actions->size()+1; i++) {
            std::string name;
            if(i==0) name = "EventsBeforeSelection";
            else name = _actions->at(i-1)->getName();
            TParameter<int>(name.c_str(), _cutflow[i]).Write(("cut"+to_string(i)).c_str());
        }
        _file->Close();
    }
}

void Analyzer::setOutput(std::string filename) {
    _writeFile = true;
    _filename = filename;
}
