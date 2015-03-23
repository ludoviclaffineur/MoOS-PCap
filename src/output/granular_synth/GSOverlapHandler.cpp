//
//  GSOverlapHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSOverlapHandler.h"

using namespace output::granular_synth;

GSOverlapHandler::GSOverlapHandler(GranularSyntheziser* GS) : GSParametersHandler("GSOverlap",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSOverlapHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSOverlapHandler::sendData(){

    mGranularSynth->setOverlap((mValueBeforeSending)*GS_MAX_OVERLAP);
    return true;
}