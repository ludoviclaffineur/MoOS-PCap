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

#include <boost/serialization/nvp.hpp>

namespace output{
namespace midi{

class MidiNoteDurationHandler : public OutputsHandler{
public:
    MidiNoteDurationHandler();
    MidiNoteDurationHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
    void setOutputDevice(void* device);
private:
    MidiNoteHandler* mMidiNoteHandler;
    void setMinDuration(int minDuration);
    void setMaxDuration(int maxDuration);
    int mMinDuration;
    int mMaxDuration;
    void updateConverter();
    friend class boost::serialization::access;
    //friend std::ostream & operator<<(std::ostream &os, Grid &g);
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {

        ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this))
           & boost::serialization::make_nvp("minDuration",mMinDuration)
           & boost::serialization::make_nvp("MaxDuration",mMaxDuration);
    }
};

}
}
#endif /* defined(__MoOS__MidiNoteDurationHandler__) */
