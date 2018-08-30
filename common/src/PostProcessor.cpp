//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    PostProcessor.cpp
// Author:  Joscha Knolle
// Date:    2018-05-14
//----------------------------------------------------------------------------//

#include <iostream>

#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

/*$#{INCLUDES}#$*/

class /*$#{NAME}#$*/ {
public:
    typedef bool (/*$#{NAME}#$*/::*Condition)();
    typedef double (/*$#{NAME}#$*/::*Weight)();
    typedef TTree* (/*$#{NAME}#$*/::*Open)();
    typedef void (/*$#{NAME}#$*/::*Close)();

    struct StreamContainer {
        Open open;
        Close close;
        Condition condition;
        Weight weight;
        TString title;
        StreamContainer() :
            open(nullptr), close(nullptr), condition(nullptr), weight(nullptr), title("") {}
        StreamContainer(Open o, Close cl, Condition co, Weight w, TString t) :
            open(o), close(cl), condition(co), weight(w), title(t) {}
    };

    /*$#{NAME}#$*/();
    void run();
    void action(int, double);

    TTreeReader _reader;
    StreamContainer* _streams;
    int _n_streams;
    TFile* _file;
    TChain* _chain;

    /*$#{DEFINITIONS}#$*/

};

/*$#{NAME}#$*/::/*$#{NAME}#$*/() :
    _n_streams(/*$#{NSTREAMS}#$*/),
    _streams(new StreamContainer[/*$#{NSTREAMS}#$*/])
    /*$#{INITIALIZATIONS}#$*/
{
    /*$#{CONSTRUCTIONS}#$*/
}

void /*$#{NAME}#$*/::action(int nStream, double weight) {
    /*$#{ACTION}#$*/
}

void /*$#{NAME}#$*/::run() {
    // Loop over all streams
    for(int nStream=0; nStream<_n_streams; nStream++) {
        StreamContainer* stream = _streams+nStream;
        TTree* tree = (this->*stream->open)();
        _reader.SetTree(tree);
        while(_reader.Next()) {
            if(!(this->*stream->condition)())
                continue;
            double weight = (this->*stream->weight)();
            action(nStream, weight);
        }
        (this->*stream->close)();
    }

    /*$#{OUTPUTS}#$*/
}

void /*$#{NAME}#$*/_main() {
    /*$#{NAME}#$*/ processor;
    processor.run();
}
