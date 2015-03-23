//
//  PcapProcessings.h
//  MoOS
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapProcessings__
#define __MoOS__PcapProcessings__

#include "Processings.h"
#include "IpHeaderDefinitions.h"
#include <arpa/inet.h>

namespace processing{
namespace pcap{

class PcapProcessings : public Processings {
public:
        PcapProcessings(){};
        void setActive(bool active) = 0;
        //virtual void process(const u_char* datas) = 0;
        virtual void process (const u_char* data) =0;
        void process(void* vdata){
            process (*((const u_char**) vdata));
        };
        virtual void setSetter(int nbrSetter,...){

        }
};

}
}


#endif /* defined(__MoOS__PcapProcessings__) */
