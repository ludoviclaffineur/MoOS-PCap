//
//  PcapKissProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 15/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapKissProcessing__
#define __MoOS__PcapKissProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "LocationIp.h"
#include <vector>
#include <lo/lo.h>
#include <string.h>
#include <regex>
#include "string.h"

namespace processing{
namespace pcap{

namespace KISS {

    enum TRAFFIC{
        IN=0,
        OUT=1
    };
}
class Spectator{

public:
    Spectator(int identifier,long int ipAddress, int interval=3){
        mId = identifier;
        mIpAdress =ipAddress;
        mInterval = interval;
        mAmountDataIn = 0;
        mAmountDataOut = 0;
        mDistance = 0.0;
        mCountPacket = 0;
        mLastTick = time(NULL);
    }

    float getMeanDistance(){
        if (mCountPacket>0) {
            return mDistance/(float)mCountPacket;
        }
        return 0;

    };

    float getBandwidthIn(){
        return mAmountDataIn/(float) mInterval;
    }

    float getBandwidthOut(){
        return mAmountDataOut/(float) mInterval;
    }

    int getId(){
        return mId;
    }

    void addPacket(int typeOfTraffic, int dataAmout, float distance ){
        switch (typeOfTraffic) {
            case KISS::TRAFFIC::IN:
                mAmountDataIn+= dataAmout;
                break;
            case KISS::TRAFFIC::OUT:
                mAmountDataOut+= dataAmout;
                break;
            default:
                break;
        }

        mDistance += distance;
        mCountPacket++;
    }
    long int getIpAdress(){
        return mIpAdress;
    }

    time_t getTime(){
        return mLastTick;
    }
    void reset(){
        mLastTick = time(NULL);
        mAmountDataIn = 0;
        mAmountDataOut = 0;
        mDistance = 0.0;
        mCountPacket = 0;

    }
private:
    int mId;
    int mAmountDataIn;
    int mAmountDataOut;
    int mCountPacket;
    float mDistance;
    int mInterval;
    long int mIpAdress;
    std::time_t mLastTick;

};




class PcapKissProcessing : public PcapProcessings{
public:
    PcapKissProcessing();
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);

private:
    std::time_t mLastTick;
    Spectator*    SpectatorWithIpAddress(long int ipadd);
    LocationIp**        mIpLocations;
    bool isLocalAddress(long int ipadd);
    LocationIp* findLocationFromIpAddress(unsigned long int TargetIp);
    LocationIp* binaryTree(unsigned long int TargetIp);
    float getDistance(const u_char* data);
    float haversine (LocationIp* home, LocationIp* server);
    std::vector<Spectator*> audience;
    lo_address mDistant;
    char* mIpAddress;
    char* mPort;
};

}
}

#endif /* defined(__MoOS__PcapKissProcessing__) */
