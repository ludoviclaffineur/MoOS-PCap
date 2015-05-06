//
//  GSBlankHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__GSBlankHandler__
#define __MoOS__GSBlankHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"
namespace output{
namespace granular_synth{
class GSBlankHandler: public GSParametersHandler{
public:

    GSBlankHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    int GS_MAX_BLANK;
private:

};
}
}
#endif /* defined(__MoOS__GSBlankHandler__) */
