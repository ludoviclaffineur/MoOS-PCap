//
//  GSBlankHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSBlankHandler.h"

using namespace output::granular_synth;
GSBlankHandler::GSBlankHandler(GranularSyntheziser* GS) : GSParametersHandler("GSBlank",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSBlankHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSBlankHandler::sendData(){
    mGranularSynth->setBlank((1-mValueBeforeSending)*GS_MAX_BLANK);
    return true;
}