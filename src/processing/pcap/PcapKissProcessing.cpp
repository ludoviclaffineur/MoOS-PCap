
//  PcapKissProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 15/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapKissProcessing.h"
#include "CsvImporter.h"
#include <math.h>
#include <sstream>
using namespace processing::pcap;
/// @brief The usual PI/180 constant
static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
/// @brief Earth's quatratic mean radius for WGS-84
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

PcapKissProcessing::PcapKissProcessing(){
    std::string csvstring ="/Users/ludoviclaffineur/Documents/MoOS/CMAKE/IpGps.csv";
    mIpLocations = CsvImporter::importCsv(csvstring);
    mLastTick = time(NULL);
    if (mIpLocations == NULL){
        mActive = false;
    }
    else{
        mActive = true;
    }
    mDistant = lo_address_new("192.168.240.89", "8000");
}

void PcapKissProcessing::process(const u_char *data){
    if (mActive) {
        ip_header *ih;
        ih = (ip_header *) (data + 14);
        u_char ihl = ih->ver_ihl>>4;
        ihl = ihl<<4;
        ihl = ih->ver_ihl - ihl;

        tcp_header* tcp;
        tcp  = (tcp_header*)(data + 14 + sizeof(ip_header) - sizeof(u_int));
        u_short dport = ntohs(tcp->dport);
        //std::cout<<"TOS " << (u_short)ihl << " PORT " << dport <<std::endl;

        if(ih->proto == 6 && (dport == 993 || dport == 995 || dport == 110 || dport == 143)){
            std::cout<<"MAIL " << std::endl;
        }
        long int ipadd =ntohl(ih->saddr.int_address);
        ip_address ipAdressSt = ih->saddr;
        float distance = getDistance(data);
        int InOrOut;
        if( isLocalAddress(ipadd)){
            InOrOut = KISS::TRAFFIC::OUT;
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
        }
        else{
            InOrOut = KISS::TRAFFIC::IN;
            ipadd = ntohl(ih->daddr.int_address);
            ipAdressSt = ih->daddr;
        }

        if(isLocalAddress(ipadd)){


            Spectator* s = SpectatorWithIpAddress(ipadd);

            s->addPacket(InOrOut, ih->tlen, distance);

            if (mLastTick+2 < time(NULL)) {
                for (int i =0; i<audience.size(); i++) {

                    std::cout<<"USERS " << audience[i]->getId() <<" \tDISTANCE " << audience[i]->getMeanDistance() << "\t BANDWITH IN " << audience[i]->getBandwidthIn()/1024.0 << "\t BANDWITH OUT "<< audience[i]->getBandwidthOut()/ 1024.0/1024.0<<std::endl;


                    std::stringstream bandwidthOutString ;
                    bandwidthOutString << "/bandwidthOut/";
                    std::stringstream bandwidthInString ;
                    bandwidthInString << "/bandwidthIn/" ;
                    std::stringstream meanDistanceString ;
                    meanDistanceString << "/meanDistance/";
                    if(audience[i]->getId() < 9){
                        bandwidthOutString<< 0;
                        bandwidthInString << 0;
                        meanDistanceString << 0;

                    }
                    bandwidthOutString  <<audience[i]->getId()+1;
                    bandwidthInString  <<audience[i]->getId()+1;
                    meanDistanceString << audience[i]->getId()+1;


                    lo_send(mDistant, bandwidthOutString.str().c_str(), "f", audience[i]->getBandwidthOut()/ 8.0 / 10.0 /1024.0/1024.0);
                    lo_send(mDistant, bandwidthInString.str().c_str(), "f", audience[i]->getBandwidthIn()/ 8.0/ 10.0/1024.0/1024.0);
                    lo_send(mDistant, meanDistanceString.str().c_str(), "f", audience[i]->getMeanDistance());

                    std::cout << meanDistanceString.str().c_str()<< std::endl;
                    audience[i]->reset();
                    mLastTick = time(NULL);
                }


                
                //i->struct_bytes.byte1;
                

            }
        }

    }
}


Spectator* PcapKissProcessing::SpectatorWithIpAddress(long int ipadd){
    bool found=false;
    for (int i=0; i<audience.size(); i++) {
        if (audience[i]->getIpAdress() == ipadd) {
            found = true;
            return audience[i];
        }
    }

    Spectator* s= new Spectator((int)audience.size(),ipadd);
    audience.push_back(s);
    lo_send(mDistant, "/newUser", "f", (float)s->getId());
    return s;
}

void PcapKissProcessing::setActive(bool active){
    mActive = active;
}

bool PcapKissProcessing::isLocalAddress(long int ipadd){
    return ((ipadd > TEN_ZERO_ZERO_ZERO && ipadd <= TEN_FIFTY_TWO) || (ipadd > ONE_SEVENTY_TWO_MIN && ipadd <= ONE_SEVENTY_TWO_MAX) || (ipadd > ONE_NINETY_TWO_MIN && ipadd <= ONE_NINETY_TWO_MAX));
}


float PcapKissProcessing::getDistance(const u_char *data){
    ip_header *ih;
    ih = (ip_header *) (data + 14);
    long int ipadd =ntohl(ih->saddr.int_address);
    //std::cout<<"Adresse IP "<<ipadd <<std::endl;

    LocationIp* from;
    LocationIp* to;
    if(isLocalAddress(ipadd)){
        //std::cout<<"Je suis dedans" <<std::endl;
        //mGrid->getInputWithName("SourceLatitude")->setValue(51);
        //mGrid->getInputWithName("SourceLongitude")->setValue(4);
        from = new LocationIp(ipadd, 51,  4);


        ipadd = ntohl(ih->daddr.int_address);
        if( isLocalAddress(ipadd) ){
            to = new LocationIp(ipadd, 51,  4);
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
        }
        else{
            LocationIp* l = findLocationFromIpAddress(ipadd);
            if(l){
                to = new LocationIp(ipadd, l->getLatitude(),  l->getLongitude());
                //mGrid->getInputWithName("DestLatitude")->setValue(l->getLatitude());
                //mGrid->getInputWithName("DestLongitude")->setValue(l->getLongitude());
            }
        }
        //std::cout<< "LOCAL NETWORK"<< std::endl;
    }
    else{
        LocationIp* l = findLocationFromIpAddress(ntohl(ih->saddr.int_address));
        if(l){
            to = new LocationIp(ipadd, 51,  4);
            from = new LocationIp(ipadd, l->getLatitude(),  l->getLongitude());
            //mGrid->getInputWithName("SourceLatitude")->setValue(l->getLatitude());
            //mGrid->getInputWithName("SourceLongitude")->setValue(l->getLongitude());
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
            //std::cout<< "EXTERNAL NETWORK"<< std::endl;
        }
    }
    if (from && to){
        return haversine(from, to);
    }
    else{
        return 0;
    }

}

LocationIp* PcapKissProcessing::findLocationFromIpAddress(unsigned long int TargetIp){
    return binaryTree(TargetIp);
    //return PcapHandler::Secante(TargetIp, p);
}

LocationIp* PcapKissProcessing::binaryTree(unsigned long int TargetIp){
    int min = 0, max = NBR_IP_ADDRESSES-1;
    int middle;
    int i;
    for( i = 0; i<30; i++){
        middle = (max+min)/2;
        if (TargetIp >= mIpLocations[middle]->getIpBegin() && TargetIp < mIpLocations[middle+1]->getIpBegin()) {
            //std::cout<<"Nbr iterations = " << i <<std::endl;
            return mIpLocations[middle];
        }
        else{
            if (TargetIp >= mIpLocations[middle]->getIpBegin() && TargetIp <= mIpLocations[max]->getIpBegin()) {
                min = middle;
            }
            else{
                max= middle;
            }
        }
    }

    return NULL;
}

float PcapKissProcessing::haversine (LocationIp* from, LocationIp* to){
    double latitudeArc  = (from->getLatitude() - to->getLatitude()) * DEG_TO_RAD;
    double longitudeArc = (from->getLongitude() - to->getLongitude()) * DEG_TO_RAD;
    double latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    double lontitudeH = sin(longitudeArc * 0.5);
    lontitudeH *= lontitudeH;
    double tmp = cos(from->getLatitude()*DEG_TO_RAD) * cos(to->getLatitude()*DEG_TO_RAD);
    return 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH))/3.1416;
}

