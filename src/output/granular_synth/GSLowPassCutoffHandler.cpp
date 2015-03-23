//
//  GSLowPassCutoffHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSLowPassCutoffHandler.h"

using namespace output::granular_synth;
GSLowPassCutoffHandler::GSLowPassCutoffHandler(GranularSyntheziser* GS) : GSParametersHandler("GSLowPassCutoff",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSLowPassCutoffHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSLowPassCutoffHandler::sendData(){
    mGranularSynth->setCutoff((mValueBeforeSending)*GS_MAX_Cutoff);
    return true;
}