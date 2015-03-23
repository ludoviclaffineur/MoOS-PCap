//
//  CsvRow.h
//  MoOS
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__LocationIp__
#define __MoOS__LocationIp__

#include <iostream>
class LocationIp{
public:
    LocationIp(unsigned long int ipbegin, short int latitude, short int longitude);
    unsigned long int getIpBegin();
    short int getLongitude();
    short int getLatitude();
private:
    unsigned long int mIpBegin;  //need 4 bytes for IP address
    short int mLatitude;
    short int mLongitude;

};

#endif /* defined(__MoOS__CsvRow__) */
