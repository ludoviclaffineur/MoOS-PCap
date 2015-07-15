//
//  LeapHandsProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 4/11/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__LeapHandsProcessing__
#define __MoOS__LeapHandsProcessing__

#include "LeapProcessing.h"
#include "Grid.h"

namespace processing{
namespace leapmotion{
        using namespace mapping;
class LeapHandsProcessing :public LeapProcessing{
public:
    LeapHandsProcessing(Grid* g);
    void process (const Leap::Controller& controller);
    void setActive(bool active);
private:
    void setSetter(int nbrSetter,...);


};
}
}

#endif /* defined(__MoOS__LeapHandsProcessing__) */
