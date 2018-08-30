//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    MonteCarloWeights.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "Mode.h"
#include "MonteCarloWeights.h"
#include "Sample.h"

float MonteCarloWeights::execute(Event* ev) {
    double weight = 1.0;
    if((ev->sample()&Sample::MonteCarlo)!=0 && (ev->mode()&Mode::MonteCarlo)!=0)
        weight *= ev->weightMENominal();
    return weight;
}
