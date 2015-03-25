//
//  MidiControlChange.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 21/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiControlChange.h"

using namespace output::midi;

MidiControlChange::MidiControlChange(): OutputsHandler("MidiControlChange"){
        mOutputType = CONSTANCES::MIDI;
        mParameters.push_back(new Parameter<unsigned short>("cc", &mController));
        mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
        mParameters.push_back(new Parameter<unsigned short>("MinCCValue", &mMinMidi));
        mParameters.push_back(new Parameter<unsigned short>("MaxCCValue", &mMaxMidi));
}

MidiControlChange::MidiControlChange(MidiHandler* mh, std::string name): OutputsHandler(name){
    mOutputType = CONSTANCES::MIDI;
    mMidiHandler = mh;
    mController = 1;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 127);
    mMinMidi = 0;
    mMaxMidi = 127;
    mParameters.push_back(new Parameter<unsigned short>("cc", &mController));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<unsigned short>("MinCCValue", &mMinMidi));
    mParameters.push_back(new Parameter<unsigned short>("MaxCCValue", &mMaxMidi));
}

MidiControlChange::MidiControlChange(MidiHandler* mh, int controller, std::string name,int midiMin, int midiMax): MidiControlChange(mh,controller,name){

    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,midiMin, midiMax);
    mMinMidi = midiMin;
    mMaxMidi = midiMax;

}

MidiControlChange::MidiControlChange(MidiHandler* mh, int controller,std::string name): MidiControlChange(mh,name){
    mController = controller;
}


bool MidiControlChange::sendData(){
    std::cout<< "CC "<< mController << " " << mValueBeforeSending <<std::endl;
    mMidiHandler->sendControlChange(mController, mValueBeforeSending);
    return true;
}
void MidiControlChange::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("cc")==0) {
            setControllerId(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if (ParameterList.at(i).compare("MinCCValue")==0) {
            setMinCCValue(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if (ParameterList.at(i).compare("MaxCCValue")==0) {
            setMaxCCValue(std::atoi(ParameterList.at(i+1).c_str()));
        }
    }
}

void MidiControlChange::setControllerId(unsigned char newController){
    mController = newController;
}

void MidiControlChange::setMaxCCValue(int max){
    if(max <=127 && max >=0 ){
        mMaxMidi = max;
    }
}

void MidiControlChange::setMinCCValue(int min){
    if(min <=127 && min >=0 ){
        mMinMidi = min;
    }
}

void MidiControlChange::updateConverter(){
    mConverter->setYMin(mMinMidi);
    mConverter->setYMax(mMaxMidi);

}