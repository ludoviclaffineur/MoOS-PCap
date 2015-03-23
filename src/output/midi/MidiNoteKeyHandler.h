//
//  MidiKeyHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__MidiNoteKeyHandler__
#define __MoOS__MidiNoteKeyHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
#include "AppIncludes.h"
namespace output{
namespace midi{

class MidiNoteKeyHandler : public OutputsHandler{
public:
    MidiNoteKeyHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);

private:
    MidiNoteHandler* mMidiNoteHandler;
    void setMinKey(int minKey);
    void setMaxKey(int maxKey);
    int mMinKey;
    int mMaxKey;
    void updateConverter();
};
}
}

#endif /* defined(__MoOS__MidiKeyHandler__) */
