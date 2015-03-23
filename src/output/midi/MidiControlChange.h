//
//  MidiControlChange.h
//  MoOS
//
//  Created by Ludovic Laffineur on 21/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__MidiControlChange__
#define __MoOS__MidiControlChange__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiHandler.h"
#include "AppIncludes.h"

namespace output{
namespace midi{

class MidiControlChange : public OutputsHandler{
public:
    MidiControlChange(MidiHandler* mh, int controller, std::string name);
    MidiControlChange(MidiHandler* mh, int controller, std::string name, int midiMin, int midiMax);
    MidiControlChange(MidiHandler* mh ,std::string name);
    bool sendData();
    void setControllerId(unsigned char newController);
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiHandler* mMidiHandler;
    unsigned short mController;
    unsigned short mMinMidi;
    unsigned short mMaxMidi;
    void setMaxCCValue(int max);
    void setMinCCValue(int min);
    void updateConverter();
};
}
}
#endif /* defined(__MoOS__MidiControlChange__) */
