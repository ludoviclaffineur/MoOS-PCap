//
//  GSDurationHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSParametersHandler.h"
using namespace output::granular_synth;
GSParametersHandler::GSParametersHandler(const char* n,GranularSyntheziser* GS):OutputsHandler(n){
    mGranularSynth = GS;
    mOutputType = CONSTANCES::GRANULAR_SYNTH;
}

void GSParametersHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
    }
}