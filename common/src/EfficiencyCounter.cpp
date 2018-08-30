//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EfficiencyCounter.cpp
// Author:  Joscha Knolle
// Date:    2018-05-08
//----------------------------------------------------------------------------//

#include <TDirectory.h>
#include <TParameter.h>

#include "EfficiencyCounter.h"
#include "Jet.h"
#include "Lepton.h"

template <typename T> void EfficiencyCounter<T>::write(std::string name) {
    std::string dirname = directoryName();
    if(!gDirectory->cd(dirname.c_str()) && dirname.find(gDirectory->GetName())!=0) {
        gDirectory->mkdir(dirname.c_str(), "Efficiencies");
        gDirectory->cd(dirname.c_str());
        TParameter<int>("beforeConditions", _failedObjects+_passedObjects).Write("beforeConditions");
    }
    std::string parname = "after"+name+std::to_string(_counter);
    TParameter<int>(parname.c_str(), _passedObjects).Write(parname.c_str());
}

// Specialization for leptons
int leptonCounter = 0;
template <> EfficiencyCounter<Lepton>::EfficiencyCounter() :
    _passedObjects(0), _failedObjects(0), _counter(++leptonCounter)
{}
template <> std::string EfficiencyCounter<Lepton>::directoryName() {
    return "leptonEfficiencies";
}
template class EfficiencyCounter<Lepton>;

// Specialization for jets
int jetCounter = 0;
template <> EfficiencyCounter<Jet>::EfficiencyCounter() :
    _passedObjects(0), _failedObjects(0), _counter(++jetCounter)
{}
template <> std::string EfficiencyCounter<Jet>::directoryName() {
    return "jetEfficiencies";
}
template class EfficiencyCounter<Jet>;
