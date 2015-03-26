//
//  PcapLocationProcessing.h
//  MoOS
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapLocationProcessing__
#define __MoOS__PcapLocationProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "Grid.h"
#include "LocationIp.h"
#include "CsvImporter.h"
#include <stdarg.h>
#include <boost/function.hpp>
#include "Setter.h"
#include "Input.h"
//#include <boost/bind.hpp>


namespace processing{
namespace pcap{
        using namespace mapping;
class PcapLocationProcessing : public PcapProcessings{

public:
    //typedef boost::function<void (Setter, double )> SetterFct;
    //typedef void (*Setter)(float value);
    PcapLocationProcessing(Grid* g);
    ~PcapLocationProcessing();
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);
    //void process();
    void setSetter(Setter<float>* setSourceLattitude, Setter<float>*  setSourceLongitude, Setter<float>*  setDestinationLattitude, Setter<float> *setDestinationLongitude){
        setSetter(4, setSourceLattitude,setSourceLongitude,setDestinationLattitude,setDestinationLongitude);
    }
    static float haversine (LocationIp* home, LocationIp* server);
    void setGrid(Grid* g){
        mGrid = g;
    }
private:
    LocationIp** mIpLocations;
    Grid* mGrid;

    bool isLocalAddress(long int ipadd);
    LocationIp* findLocationFromIpAddress(unsigned long int TargetIp);

    LocationIp* binaryTree(unsigned long int TargetIp);
    LocationIp* secante(unsigned long int TargetIp);
    //SetterFct mSetSourceLattitude,mSetSourceLongitude,mSetDestinationLattitude,mSetDestinationLongitude;
    Setter<float> * mSourceLat;
    Setter<float> * mSourceLong;
    Setter<float> * mDestLat;
    Setter<float> * mDestLong;
    void setSetter(int nbrSetter,...);

};
}
}
#endif /* defined(__MoOS__PcapLocationProcessing__) */
