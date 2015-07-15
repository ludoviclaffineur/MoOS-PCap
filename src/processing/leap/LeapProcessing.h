//
//  LeapProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 4/11/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__LeapProcessing__
#define __MoOS__LeapProcessing__

#include "Processings.h"
#include <leap/Leap.h>

namespace processing{
namespace leapmotion{

        class LeapProcessing : public Processings{
            virtual void setActive(bool active) = 0;
            //virtual void process(const u_char* datas) = 0;
            virtual void process (const Leap::Controller& controller) =0;
            void process(void* vdata){
                process (*((const Leap::Controller*) vdata));
            };
        private:
            virtual void setSetter(int nbrSetter,...) = 0;
        };
}
}
#endif /* defined(__MoOS__LeapProcessing__) */
