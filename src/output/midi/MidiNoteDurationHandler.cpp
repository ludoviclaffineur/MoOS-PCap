//
//  MidiNoteDurationHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteDurationHandler.h"

using namespace output::midi;

MidiNoteDurationHandler::MidiNoteDurationHandler(): OutputsHandler("Duration"){
        mMinDuration = 0;
        mMaxDuration = 0;
        mParameters.push_back(new Parameter<int>("MinDuration", &mMinDuration));
        mParameters.push_back(new Parameter<int>("MaxDuration", &mMaxDuration));
}

MidiNoteDurationHandler::MidiNoteDurationHandler(MidiNoteHandler* mh):
    OutputsHandler("Duration"){
        mOutputType = CONSTANCES::MIDI;
        mMidiNoteHandler = mh;
        mMinDuration = 1677;
        mMaxDuration = 10000;
        mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,mMinDuration, mMaxDuration);
        mParameters.push_back(new Parameter<int>("MinDuration", &mMinDuration));
        mParameters.push_back(new Parameter<int>("MaxDuration", &mMaxDuration));

}

bool MidiNoteDurationHandler::sendData(){
    std::cout<<"DURATION"<<mValueBeforeSending<<std::endl;
    mMidiNoteHandler->setDuration(mValueBeforeSending);
    mMidiNoteHandler->sendMidiOnOff();

    return true;
}

void MidiNoteDurationHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("MinDuration")==0) {
            setMinDuration(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if(ParameterList.at(i).compare("MaxDuration")==0) {
            setMaxDuration(std::atoi(ParameterList.at(i+1).c_str()));
        }
    }
}

void MidiNoteDurationHandler::setMinDuration(int minDuration){
    if(minDuration>0){
        mMinDuration = minDuration;
        updateConverter();
    }
}

void MidiNoteDurationHandler::setMaxDuration(int maxDuration){
    if (maxDuration>0){
        mMaxDuration = maxDuration;
        updateConverter();
    }
}

void MidiNoteDurationHandler::updateConverter(){
    mConverter->setYMin(mMinDuration);
    mConverter->setYMax(mMaxDuration);

}