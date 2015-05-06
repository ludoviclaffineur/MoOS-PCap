//
//  GSReverbDelayHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__GSReverbDelayHandler__
#define __MoOS__GSReverbDelayHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"
namespace output{
namespace granular_synth{
class GSReverbDelayHandler: public GSParametersHandler{
public:
    GSReverbDelayHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    float GS_MAX_DELAY;
private:

};

}
}
#endif /* defined(__MoOS__GSReverbDelayHandler__) */
