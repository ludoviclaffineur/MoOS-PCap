//
//  MidiNoteVelocityHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteVelocityHandler.h"

using namespace output::midi;
MidiNoteVelocityHandler::MidiNoteVelocityHandler()/*: OutputsHandler("MidiVelocity")*/{
        mMinVelocity = mMaxVelocity = 0;
        mParameters.push_back(new Parameter<int>("MinVelocity", &mMinVelocity));
        mParameters.push_back(new Parameter<int>("MaxVelocity", &mMaxVelocity));
}


MidiNoteVelocityHandler::MidiNoteVelocityHandler(MidiNoteHandler* mh): OutputsHandler("MidiVelocity"){
    mMidiNoteHandler = mh;
    mOutputType = CONSTANCES::MIDI;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,127, 127);
    mMinVelocity = mMaxVelocity = 127;
    mParameters.push_back(new Parameter<int>("MinVelocity", &mMinVelocity));
    mParameters.push_back(new Parameter<int>("MaxVelocity", &mMaxVelocity));
    //mConverter = new Converter
}

bool MidiNoteVelocityHandler::sendData(){
    //mConverter.extrapolate(mValueBeforeSending)
    std::cout<< "VELOCITY" <<mValueBeforeSending <<std::endl;
    mMidiNoteHandler->setVelocity(mValueBeforeSending);
    return true;
}

void MidiNoteVelocityHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("MinVelocity")==0) {
            setMinVelocity(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if(ParameterList.at(i).compare("MaxVelocity")==0) {
            setMaxVelocity(std::atoi(ParameterList.at(i+1).c_str()));
        }
    }
}

void MidiNoteVelocityHandler::setMinVelocity(int minVelocity){
    if(minVelocity>0 && minVelocity<=127){
        mMinVelocity = minVelocity;
        updateConverter();
    }
}

void MidiNoteVelocityHandler::setMaxVelocity(int maxVelocity){
    if (maxVelocity>=0 && maxVelocity<=127 ){
        mMaxVelocity  = maxVelocity;
        updateConverter();
    }
}

void MidiNoteVelocityHandler::updateConverter(){
    mConverter->setYMin(mMinVelocity);
    mConverter->setYMax(mMaxVelocity);

}

void MidiNoteVelocityHandler::setOutputDevice(void* device){
    mMidiNoteHandler =  (MidiNoteHandler*) device;
}