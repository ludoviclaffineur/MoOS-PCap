//
//  PcapDhcpProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 12/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapDhcpProcessing__
#define __MoOS__PcapDhcpProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "Grid.h"

namespace processing{
namespace pcap{
        using namespace mapping;
class PcapDhcpProcessing : public PcapProcessings{
public:
    PcapDhcpProcessing(Grid* g);
    void process (const u_char* data);
    void setActive (bool active);
private:
    Grid* mGrid;
    Input* mInput;
};

}
}
#endif /* defined(__MoOS__PcapDhcpProcessing__) */
