//
//  NoteFactoryClass.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__NoteFactoryClass__
#define __MoOS__NoteFactoryClass__

#include <stdio.h>
#include "Grid.h"
#include "MidiHandler.h"
//#include "MidiNoteDurationHandler.h"
//#include "MidiNoteKeyHandler.h"
//#include "MidiNoteVelocityHandler.h"
namespace output{
namespace midi{

class MidiNote{
public:
        MidiNote(){};
    MidiNote(unsigned char key, unsigned char velocity, int duration,MidiHandler* mh);
    unsigned char mKey, mVelocity;
    int mDuration;
    MidiHandler* mMidiHandler;
};



class MidiNoteHandler{
public:
    MidiNoteHandler(MidiHandler* mh);
    void setKey(unsigned char key);
    void setDuration(int duration);
    void setVelocity(unsigned char velocity);
    void sendMidiOnOff();

    static void* tSendMidi(void* midiNote);


private:
    MidiHandler* mMidiHandler;
    unsigned char mCurrentKey;
    int mCurrentDuration;
    unsigned char mCurrentVelocity;
    std::vector<pthread_t> mThreads;
    //MidiNoteDurationHandler* mMidiNoteDurationHandler;
   // MidiNoteKeyHandler* mMidiNoteKeyHandler;
   // MidiNoteVelocityHandler* mMidiNoteVelocityHandler;
};

}
}


#endif /* defined(__MoOS__NoteFactoryClass__) */
