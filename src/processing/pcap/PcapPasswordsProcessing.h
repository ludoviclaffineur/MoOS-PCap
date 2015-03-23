//
//  PcapPasswordsProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 8/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapPasswordsProcessing__
#define __MoOS__PcapPasswordsProcessing__

#include <iostream>
#include "PcapProcessings.h"

namespace processing{
namespace pcap{
        class PcapPasswordsProcessing : public PcapProcessings {
        public:
            PcapPasswordsProcessing();
            void setActive(bool active);
            //void process(const u_char* datas);
            void process(const u_char* data);
            void setLength(int length);

        private:
            int mLength;
        };
}
}

#endif /* defined(__MoOS__PcapPasswordsProcessing__) */
