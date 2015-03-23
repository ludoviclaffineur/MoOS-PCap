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
    mInitPostion = (initPos + rand()%mWindowSize)%(audioFile->size()-mDuration);
    mBlank = blank;
    done = false;
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

//        mCurrentPostion =0.0f;
//        mInitPostion = rand()%(mAudioFile->size()-mDuration);
        done = true;
    }
    mCurrentPostion++;

    return sample;

}
//float Grain::getSample(){
//    float sample = 0.0f;
//    switch (mEnvelope) {
//        case Grain::ENVELOPE::ATTACK:
//            sample = mAudioFile->at(mInitPostion)*((float)mCurrentPostion/(float) nbrSamplesFade);
//            if (mCurrentPostion == nbrSamplesFade) {
//                mEnvelope = ENVELOPE::DELAY;
//            }
//            break;
//        case Grain::ENVELOPE::DELAY:
//            sample = mAudioFile->at(mInitPostion+mCurrentPostion);
//            if (mCurrentPostion == nbrSamplesFade + mDuration) {
//                mEnvelope = ENVELOPE::RELEASE;
//            }
//            break;
//        case Grain::ENVELOPE::RELEASE:
//            sample = mAudioFile->at(mInitPostion+mDuration)*((float)(mDuration+nbrSamplesFade+nbrSamplesFade- mCurrentPostion)/(float) nbrSamplesFade);
//            if (mCurrentPostion == nbrSamplesFade + mDuration + nbrSamplesFade) {
//                mEnvelope = ENVELOPE::STOP;
//            }
//            //std::cout<<mDuration+nbrSamplesFade+nbrSamplesFade- mCurrentPostion<<std::endl;
//            break;
//        case Grain::ENVELOPE::STOP:
//            sample = 0.0f;
//            mCurrentPostion = 0.0f;
//            mInitPostion = rand()%(mAudioFile->size()-mDuration);
//            mEnvelope = ENVELOPE::ATTACK;
//
//            break;
//        default:
//            break;
//    }
//    mCurrentPostion++;
//    return sample;
//}