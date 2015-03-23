//
//  CsvRow.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "LocationIp.h"

LocationIp::LocationIp(unsigned long int ipbegin, short int latitude, short int longitude){
    mIpBegin = ipbegin;
    mLatitude = latitude;
    mLongitude = longitude;
}

unsigned long int LocationIp::getIpBegin(){
    return mIpBegin;
}

short int LocationIp::getLatitude(){
    return mLatitude;
}

short int LocationIp::getLongitude(){
    return mLongitude;
}