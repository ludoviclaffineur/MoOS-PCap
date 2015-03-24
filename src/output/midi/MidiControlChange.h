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

#include <boost/serialization/nvp.hpp>

#include <boost/serialization/string.hpp>

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
    friend class boost::serialization::access;
    //friend std::ostream & operator<<(std::ostream &os, Grid &g);
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {

        ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this));
        ar & boost::serialization::make_nvp("Controller",mController)
           & boost::serialization::make_nvp("minMidi",mMinMidi)
           & boost::serialization::make_nvp("maxMidi",mMaxMidi);
    }
};
}
}
#endif /* defined(__MoOS__MidiControlChange__) */
