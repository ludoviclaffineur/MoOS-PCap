//
//  GSDurationHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSDurationHandler.h"
using namespace output::granular_synth;
GSDurationHandler::GSDurationHandler(GranularSyntheziser* GS) : GSParametersHandler("GSDuration",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSDurationHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSDurationHandler::sendData(){
    //std::cout<<mValueBeforeSending<<std::endl;
    mGranularSynth->setDuration(mValueBeforeSending*GS_MAX_DURATION);
    return true;
}