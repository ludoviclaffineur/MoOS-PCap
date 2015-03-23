//
//  PcapDnsProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 24/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapDnsProcessing.h"

using namespace processing::pcap;
using namespace output;
PcapDnsProcessing::PcapDnsProcessing(){
    //OscOutputParent = new OscHandler("DNS Parent ouputs","127.0.0.1", "20000", "/parentNode", "is");
    //OscOutputChild = new OscHandler("DNS Child ouputs","127.0.0.1", "20000", "/childNode", "is");
    mCurrentIdNode= 0;
    mOscIpAddress = lo_address_new("192.168.240.89", "8000");
}

PcapDnsProcessing::~PcapDnsProcessing(){
    lo_address_free(mOscIpAddress);
    mOscIpAddress = NULL;
}

void PcapDnsProcessing::process(const u_char *data){
    ip_header *ih;
    ih = (ip_header *) (data + 14);
    if (ih->proto == 17){
        udp_header* uh = (udp_header*)(data + 14 + sizeof(ip_header) - sizeof(u_int));
        //printf("DEST PORT = %d \n", uh->dport);
        if (ntohs(uh->dport) == 53){
            //printf("DEST PORT = %d \n", ntohs(uh->dport));
            ip_header *ih;
            ih = (ip_header *) (data + 14);
            long int ipadd =ntohl(ih->saddr.int_address);



            const u_char* payload =(const u_char*) (data + 14 + sizeof(ip_header) - sizeof(u_int) + sizeof(udp_header));
            payload+=12;   // matches words beginning by "sub"

            std::stringstream s;
            s<< payload;
            //std::cout<<s.str() << std::endl;
            std::string theRequest = s.str();
            for (int i=0; i< theRequest.length(); i++) {
                if(theRequest[i] < '.'){
                    theRequest[i]='.';
                }
            }
            std::string token = theRequest.substr(0, theRequest.find_last_of('.'));

            //std::cout<<token << std::endl;
            //std::cout<< token.find_last_of(delimiter)<< " size: " << token.length()<<std::endl;

            token = token.substr(token.find_last_of('.')+1,token.length());


            if (std::strcmp(token.c_str(), "facebook") ==0) {
                std::cout<<"Facebook"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "google") ==0) {
                std::cout<<"google"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "bing") ==0) {
                std::cout<<"bing"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "twitter") ==0) {
                std::cout<<"twitter"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "gmail") ==0) {
                std::cout<<"gmail"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "snapchat") ==0) {
                std::cout<<"snapchat"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            else if (std::strcmp(token.c_str(), "instagram") ==0) {
                std::cout<<"instagram"<<std::endl;
                lo_send(mOscIpAddress, "/facebook", "i", rand());
            }
            std::cout<< "FINAL = " <<token<<std::endl;
            DnsClient* client=clientExists(ipadd);
            if (!client) {
                client = new DnsClient(ipadd);
                mListClients.push_back(client);
            }
            if (client->isParentNode()) {
                sendParentNode(++mCurrentIdNode, token);
                client->updateParentTime(mCurrentIdNode);
            }
            else{
                sendChild(client->getIdNode(),token);
                client->updateParentTime(mCurrentIdNode);
            }
        }
    }
}

void PcapDnsProcessing::sendChild(int idNode, std::string website){
    //printf("CHILD NODE: %s - IDPARENT = %d  \n", website.c_str(), idNode);
    lo_send(mOscIpAddress, "/childNode", "is", idNode, website.c_str());
}

void PcapDnsProcessing::sendParentNode(int idNode, std::string website){
    //printf("PARENT NODE %d: %s \n", idNode,website.c_str());
    lo_send(mOscIpAddress, "/parentNode", "is", idNode, website.c_str());
}

DnsClient* PcapDnsProcessing::clientExists(long int ipAddress){
    std::vector<DnsClient*>::iterator i;
    for (i= mListClients.begin(); i!=mListClients.end();i++ ){
        if((*i)->getIpAddress() == ipAddress){
            return (*i);
        }
    }
    return NULL;
}


const char* PcapDnsProcessing::rleDecompress(const u_char* payload){
    int count;
    char c;
    int TOTAL = 0;
    while (*payload != '\0' && TOTAL != 42)
    {
        count = *(payload++);
        c = *(reinterpret_cast<const char*>(payload++));
        for (int i = 0; i < count; i++)
        {
            printf("%c", c);
            std::cout<<std::flush;
        }
        TOTAL++;
    }
    return NULL;
}

void PcapDnsProcessing::setActive(bool active){
    mActive = active;
}

bool PcapDnsProcessing::isDnsRequest(ip_header ih, udp_header uh){
    return false;
}


DnsClient::DnsClient(long int ipAddress){
    mIpAddress = ipAddress;
    time(&mFirstRequestTime);
}

bool DnsClient::isParentNode(){
    time_t timer;
    time(&timer);
    //std::cout << mIpAddress <<" time "<< difftime(mFirstRequestTime, timer) << std::endl;
    return (difftime(mFirstRequestTime, timer) < -1.0);
}

void DnsClient::updateParentTime(int idNode){
    time(&mFirstRequestTime);
    mIdNode = idNode;
}

long int DnsClient::getIpAddress(){
    return mIpAddress;
}
int DnsClient::getIdNode(){
    return mIdNode;
}