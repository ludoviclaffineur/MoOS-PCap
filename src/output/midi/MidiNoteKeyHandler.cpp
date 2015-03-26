//
//  MidiKeyHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteKeyHandler.h"
using namespace output::midi;

MidiNoteKeyHandler::MidiNoteKeyHandler()/*: OutputsHandler("MidiVelocity")*/{
        mOutputType = CONSTANCES::MIDI;
        mMinKey = 0;
        mMaxKey = 0;
        mParameters.push_back(new Parameter<int>("MinKey", &mMinKey));
        mParameters.push_back(new Parameter<int>("MaxKey", &mMaxKey));
}
MidiNoteKeyHandler::MidiNoteKeyHandler(MidiNoteHandler* mh):OutputsHandler("MidiKey"){
    mMidiNoteHandler = mh;
    mOutputType = CONSTANCES::MIDI;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,111, 33);

    mMinKey = 111;
    mMaxKey = 33;
    mParameters.push_back(new Parameter<int>("MinKey", &mMinKey));
    mParameters.push_back(new Parameter<int>("MaxKey", &mMaxKey));
    //mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    //mConverter = new Converter
}

bool MidiNoteKeyHandler::sendData(){
    std::cout << "KEY SENT" <<mValueBeforeSending<< std::endl;
        mMidiNoteHandler->setKey(mValueBeforeSending);
    return true;
}

void MidiNoteKeyHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("MinKey")==0) {
            setMinKey(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if(ParameterList.at(i).compare("MaxKey")==0) {
            setMaxKey(std::atoi(ParameterList.at(i+1).c_str()));
        }
    }
}


void MidiNoteKeyHandler::setMinKey(int minKey){
    if(minKey>=0 && minKey <=127){
        mMinKey = minKey;
        updateConverter();

    }
}

void MidiNoteKeyHandler::setMaxKey(int maxKey){
    if(maxKey>=0 && maxKey <=127){
        mMaxKey = maxKey;
        updateConverter();
    }
}

void MidiNoteKeyHandler::updateConverter(){
    mConverter->setYMax(mMaxKey);
    mConverter->setYMin(mMinKey);
}

void MidiNoteKeyHandler::setOutputDevice(void* device){
    mMidiNoteHandler =  (MidiNoteHandler*) device;
}