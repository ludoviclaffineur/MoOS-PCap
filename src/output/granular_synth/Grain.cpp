//
//  Grain.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "Grain.h"
#include <iostream>
#include <math.h>
using namespace output::granular_synth;

Grain::Grain(std::vector<float>* audioFile, int duration,int blank, int initPos){
    mDuration = duration;
    mWindowSize = 10000;
    mCurrentPostion=0;
    mEnvelope = ENVELOPE::ATTACK;
    mAudioFile = audioFile;
    //std::cout<<initPos<<std::endl;
    mInitPostion = (initPos + rand()%mWindowSize)%(audioFile->size()-mDuration-mWindowSize);
    mBlank = blank;
    done = false;
    nbrSamplesFade = 20;
}

float Grain::getSample(){
    float sample = 0.0f;
    if (mCurrentPostion <mDuration) {
        float hanningCoeff = 0.5 - 0.5* cosf(2*M_PI *(float)mCurrentPostion/(float)(mDuration));
        sample = mAudioFile->at(mInitPostion+mCurrentPostion)*hanningCoeff;
    }
    else if(mCurrentPostion< mDuration+ mBlank){
        sample = 0.0f;
    }
    else{
        done = true;
    }
    mCurrentPostion++;
    return sample;
}
