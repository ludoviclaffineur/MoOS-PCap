//
//  GSInitPositionHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSInitPositionHandler.h"

using namespace output::granular_synth;
GSInitPositionHandler::GSInitPositionHandler(GranularSyntheziser* GS) : GSParametersHandler("GSInitPosition",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
    GS_MAX_POSITION = (int)GS->music->size();
}

void GSInitPositionHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSInitPositionHandler::sendData(){
    //std::cout<<mValueBeforeSending << "      "<< GS_MAX_POSITION << std::endl;
    mGranularSynth->setInitPosition(mValueBeforeSending*GS_MAX_POSITION);
    return true;
}