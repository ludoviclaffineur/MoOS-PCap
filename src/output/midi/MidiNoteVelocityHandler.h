//
//  MidiNoteVelocityHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__MidiNoteVelocityHandler__
#define __MoOS__MidiNoteVelocityHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
#include "AppIncludes.h"

#include <boost/serialization/nvp.hpp>

namespace output{
namespace midi{
class MidiNoteVelocityHandler : public OutputsHandler{
public:
        MidiNoteVelocityHandler();
    MidiNoteVelocityHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiNoteHandler* mMidiNoteHandler;
    void setMinVelocity(int minVelocity);
    void setMaxVelocity(int maxVelocity);
    int mMaxVelocity;
    int mMinVelocity;
    void updateConverter();
    void setOutputDevice(void* device);
    friend class boost::serialization::access;
    //friend std::ostream & operator<<(std::ostream &os, Grid &g);
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this))
           & boost::serialization::make_nvp("minVelocity",mMinVelocity)
           & boost::serialization::make_nvp("maxVelocity",mMaxVelocity);
    }
};
}
}
#endif /* defined(__MoOS__MidiNoteVelocityHandler__) */
