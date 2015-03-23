//
//  GSDurationHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__GSParametersHandler__
#define __MoOS__GSParametersHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "GranularSyntheziser.h"
#include "AppIncludes.h"
namespace output{
namespace granular_synth{

class GSParametersHandler: public OutputsHandler{
public:
    GSParametersHandler(const char* n,GranularSyntheziser* GS);
    virtual bool sendData ()=0;
    virtual void setParameters(std::vector<std::string> ParameterList);
protected:
    GranularSyntheziser* mGranularSynth;
};

}
}
#endif /* defined(__MoOS__GSDurationHandler__) */
