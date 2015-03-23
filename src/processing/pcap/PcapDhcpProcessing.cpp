//
//  PcapDhcpProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 12/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapDhcpProcessing.h"
#include <arpa/inet.h>
using namespace processing::pcap;


PcapDhcpProcessing::PcapDhcpProcessing(Grid* g){
    mGrid = g;
    mInput = new Input("DhcpRequest", 0,1,0, 1, Converter::TypeOfExtrapolation::LINEAR);
    mGrid->addInput(mInput);
}
void PcapDhcpProcessing::process (const u_char* data){

    ip_header *ih;
    ih = (ip_header *) (data + 14);
    if (ih->proto == 17){
        udp_header* uh = (udp_header*)(data + 14 + sizeof(ip_header) - sizeof(u_int));
        //printf("DEST PORT = %d \n", uh->dport);
        if (ntohs(uh->dport) == 68){
            mInput->setValue(1);
        }
        else{
            mInput->setValue(0);
        }
    }

}
void PcapDhcpProcessing::setActive (bool active){
    mActive = active;
}
