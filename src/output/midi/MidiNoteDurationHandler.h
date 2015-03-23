//
//  MidiNoteDurationHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__MidiNoteDurationHandler__
#define __MoOS__MidiNoteDurationHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
#include "AppIncludes.h"

namespace output{
namespace midi{

class MidiNoteDurationHandler : public OutputsHandler{
public:
    MidiNoteDurationHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiNoteHandler* mMidiNoteHandler;
    void setMinDuration(int minDuration);
    void setMaxDuration(int maxDuration);
    int mMinDuration;
    int mMaxDuration;
    void updateConverter();
};

}
}
#endif /* defined(__MoOS__MidiNoteDurationHandler__) */
