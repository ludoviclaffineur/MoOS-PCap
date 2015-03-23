//
//  PcapIpProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapIpProcessing.h"
#include "IpHeaderDefinitions.h"
using namespace processing::pcap;
PcapIpProcessing::PcapIpProcessing(Grid* g){
    mGrid = g;
    mGrid->addInput("TypeOfService", 1, 255, -1, 0, Converter::LINEAR);
    mGrid->addInput("TTL", 1, 255, -1, 0, Converter::LINEAR);
    mGrid->addInput("Protocol", 1, 255, -1, 0, Converter::LINEAR);
    mGrid->addInput("PacketLength", 1, 65535, -1, 0, Converter::LINEAR);

    setSetter(mGrid->getInputWithName("PacketLength"), mGrid->getInputWithName("TypeOfService"), mGrid->getInputWithName("Protocol"), mGrid->getInputWithName("TTL"));
}

void PcapIpProcessing::setActive(bool active){
    mActive = active;

}

void PcapIpProcessing::setSetter(Setter<float>* packetLength, Setter<float>* typeOfService, Setter<float>* protocol,Setter<float>* Ttl ){
    setSetter(4, packetLength,typeOfService,protocol, Ttl);
}

void PcapIpProcessing::setSetter(int nbrSetters,...){
    va_list ap;
    va_start(ap, nbrSetters);

    mPacketLength  = va_arg(ap, Setter<float>*);
    mTypeOfService = va_arg(ap, Setter<float>*);
    mProtocol = va_arg(ap, Setter<float>*);
    mTtl = va_arg(ap, Setter<float>*);
    //mSetDestinationLongitude = va_arg(ap, SetterFct);

    va_end(ap);
}

void PcapIpProcessing::process(const u_char* data){
    //const u_char *data = (const u_char *) vdata;
    ip_header *ih;
    ih = (ip_header *) (data + 14);
    mPacketLength->setValue(ih->tlen);
    mTypeOfService->setValue((u_int8_t)ih->tos);
    mProtocol->setValue((u_int8_t)ih->proto);
    mTtl->setValue((u_int8_t)ih->ttl);
}