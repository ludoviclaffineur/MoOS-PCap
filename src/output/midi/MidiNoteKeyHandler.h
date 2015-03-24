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

#include <boost/serialization/nvp.hpp>

namespace output{
namespace midi{

class MidiNoteKeyHandler : public OutputsHandler{
public:
        MidiNoteKeyHandler(){};
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
    friend class boost::serialization::access;
    //friend std::ostream & operator<<(std::ostream &os, Grid &g);
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {

        ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this))
           & boost::serialization::make_nvp("minKey",mMinKey)
           & boost::serialization::make_nvp("maxKey",mMaxKey);
    }
};
}
}

#endif /* defined(__MoOS__MidiKeyHandler__) */
