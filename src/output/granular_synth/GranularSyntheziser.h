//
//  GranularSyntheziser.h
//  MoOS
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__GranularSyntheziser__
#define __MoOS__GranularSyntheziser__

#include <stdio.h>
#include "Grid.h"
#include "portaudio.h"
#include "Grain.h"
#include <deque>
namespace output{
namespace granular_synth{

typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;

class GranularSyntheziser{

public:

    GranularSyntheziser();
    ~GranularSyntheziser();
    int getDuration();
    void setDuration(int duration);

    int getOverlap();
    void setOverlap(int overlap);

    float getVolume();
    void setVolume(float volume);

    void setBlank(int blank);
    void setDecay(float decay);
    inline float getDecay();

    void setDelay(float delay);
    inline float getDelay();

    void setInitPosition(int delay);
    inline int getInitPosition();

    paTestData *data;
    float getSample();
    std::vector <float>* music;
    std::deque <float>* mAudioWave;
    std::vector <Grain*>mGrains ;
    void    setCutoff(float cutoff);
    float   getCutoff();
    inline void flushAudioWave();
    static float reverb(std::deque <float>*mAudioWave, float sample, float delay, float decay );
    static float echo(std::deque <float>* mAudioWave, float sample, float delay, float decay );
    static float lowPassFilter(std::deque <float>* mAudioWave, float sample, float cutoff );

private:
    int mDuration;
    int mBlank;
    int mPosition;
    int mOverlap;
    float mCutoff;
    float mVolume;
    float mDecay;
    float mDelay;
    int mInitPos;
    PaStream *stream;

    bool loadWave(std::string path);
};

}
}
#endif /* defined(__MoOS__GranularSyntheziser__) */
