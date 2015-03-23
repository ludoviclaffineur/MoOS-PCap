//
//  GSReverbDecayHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__GSReverbDecayHandler__
#define __MoOS__GSReverbDecayHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

namespace output{
namespace granular_synth{

class GSReverbDecayHandler: public GSParametersHandler{
public:

    GSReverbDecayHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const float GS_MAX_DECAY = 0.5f;
private:

};

}
}

#endif /* defined(__MoOS__GSReverbDecayHandler__) */
