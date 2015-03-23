//
//  PcapDnsProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 24/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapDnsProcessing__
#define __MoOS__PcapDnsProcessing__
#include "PcapProcessings.h"
#include "IpHeaderDefinitions.h"
#include <iostream>
#include <string.h>
#include <regex>
#include <sstream>
#include "OscHandler.h"
#include <ctime>
#include <vector>
#include <lo/lo.h>


namespace processing{
namespace pcap{

using namespace output;

class DnsClient{
public:
    DnsClient(long int ipAddress);
    bool isParentNode();
    void updateParentTime(int idNode);
    long int getIpAddress();
    int getIdNode();
private:
    long int mIpAddress;
    time_t mFirstRequestTime;
    int mIdNode;

};

class PcapDnsProcessing : public PcapProcessings {
public:
    PcapDnsProcessing();
    ~PcapDnsProcessing();
    void process(const u_char* data);
    void setActive (bool active);
    const char* rleDecompress(const u_char* payload);
private:
    bool isDnsRequest(ip_header ih, udp_header uh);
    std::vector <DnsClient*> mListClients;
    OscHandler* OscOutputParent;
    OscHandler* OscOutputChild;
    DnsClient* clientExists(long int ipAddress);
    void sendParentNode(int idNode, std::string website);
    void sendChild(int idNode, std::string website);
    int mCurrentIdNode;
    lo_address mOscIpAddress;
};

}
}
#endif /* defined(__MoOS__PcapDnsProcessing__) */
