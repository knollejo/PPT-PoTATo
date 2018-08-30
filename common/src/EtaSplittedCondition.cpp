//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    EtaSplittedCondition.cpp
// Author:  Joscha Knolle
// Date:    2018-04-26
//----------------------------------------------------------------------------//

#include <TMath.h>

#include "EtaSplittedCondition.h"

template <typename T> bool EtaSplittedCondition<T>::check(T* test) {
    return (TMath::Abs(test->Eta())<_eta ? _cond1 : _cond2)->check(test);
}

template class EtaSplittedCondition<Lepton>;
template class EtaSplittedCondition<Jet>;
