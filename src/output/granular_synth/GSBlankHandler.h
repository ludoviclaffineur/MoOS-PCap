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
    const int GS_MAX_BLANK = 10000;
private:

};
}
}
#endif /* defined(__MoOS__GSBlankHandler__) */
