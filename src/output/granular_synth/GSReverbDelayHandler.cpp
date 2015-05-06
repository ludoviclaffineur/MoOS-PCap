//
//  GSReverbDelayHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSReverbDelayHandler.h"
using namespace output::granular_synth;

GSReverbDelayHandler::GSReverbDelayHandler(GranularSyntheziser* GS) : GSParametersHandler("GSReverbDelay",GS){
    GS_MAX_DELAY = 200;
    //OutputsHandler::setName("GS_Duration");
}

void GSReverbDelayHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSReverbDelayHandler::sendData(){
    mGranularSynth->setDelay((mValueBeforeSending)*GS_MAX_DELAY);
    return true;
}
