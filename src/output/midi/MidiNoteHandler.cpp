//
//  NoteFactoryClass.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteHandler.h"
#include <unistd.h>

using namespace output::midi;

MidiNoteHandler::MidiNoteHandler( MidiHandler* mh){
    mMidiHandler = mh;
    mCurrentDuration = 1000;
    mCurrentKey = 64;
    mCurrentVelocity = 90;
}

void MidiNoteHandler::setKey(unsigned char key){
    mCurrentKey=key;
}

void MidiNoteHandler::setDuration(int duration){
    mCurrentDuration = duration;
}

void MidiNoteHandler::setVelocity(unsigned char velocity){
    mCurrentVelocity=velocity;
}

void MidiNoteHandler::sendMidiOnOff(){
    pthread_t t;
     //std::cout<<"KEY: "<<(int)mCurrentKey<< " DURATION: "<< mCurrentDuration<< " Velocity " <<(int)mCurrentVelocity<< std::endl;
    pthread_create(&t,NULL,MidiNoteHandler::tSendMidi,new MidiNote(mCurrentKey,mCurrentVelocity, mCurrentDuration,mMidiHandler));
    pthread_detach(t);
//    mThreads.push_back(t);
//    for (int i = 0; i< mThreads.size(); i++) {
//        if (pthread_detach(mThreads[i]) == 0)) {
//            statements
//        }
//    }
    //mThreads
}


void* MidiNoteHandler::tSendMidi(void* midiNote){
    MidiNote* mn = (MidiNote*) midiNote;
    //std::cout<<"IN"<< mn->mDuration<<std::endl;
    mn->mMidiHandler->sendNoteOn(mn->mKey, mn->mVelocity);
    sleep(((float)(mn->mDuration))/1000.0);
    mn->mMidiHandler->sendNoteOff(mn->mKey, mn->mVelocity);
    //std::cout<<"OUT"<< std::endl;
    //pthread_join(*mn->mThread,NULL);
    //delete (mn->mThread);
    delete mn;
    return NULL;
}

// MIDINOTE

MidiNote::MidiNote(unsigned char key, unsigned char velocity, int duration,MidiHandler* mh){
    mKey = key;
    mDuration = duration;
    mVelocity = velocity;
    mMidiHandler = mh;
}

