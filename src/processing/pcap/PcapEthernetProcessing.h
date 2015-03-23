//
//  PcapEthernetProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapEthernetProcessing__
#define __MoOS__PcapEthernetProcessing__

#include <iostream>
#include "Grid.h"
#include "PcapProcessings.h"

namespace processing{
namespace pcap{
        using namespace mapping;
class PcapEthernetProcessing : public PcapProcessings{
public:
    PcapEthernetProcessing(Grid* g);
};
}
}
#endif /* defined(__MoOS__PcapEthernetProcessing__) */
