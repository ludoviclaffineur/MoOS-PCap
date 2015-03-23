//
//  CsvImporter.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "CsvImporter.h"
#include <fstream>
#include "AppIncludes.h"


LocationIp** CsvImporter::importCsv(std::string &file){
    //std::fstream filestream (file);

    LocationIp** importedData = new LocationIp*[NBR_IP_ADDRESSES];

    std::ifstream filestream (file, std::ifstream::in);
    if (filestream) {
        std::string line;
        unsigned long int IpBegin;  //need 4 bytes for IP address
        short int iLatitude;
        short int iLongitude;
        int i = 0;
        //auto begin = std::chrono::high_resolution_clock::now() ;
        std::cout<< "Loading...";
        while (filestream.good()) {
            getline(filestream, line, ',');
            IpBegin = strtol(line.c_str(),NULL, 10);
            //std::cout<< line <<std::endl;
            getline(filestream, line, ',');
            iLatitude = atoi(line.c_str());
            //std::cout<< line <<std::endl;
            getline(filestream, line, '\n');
            iLongitude = atoi(line.c_str());
            //std::cout<< line <<std::endl;
            importedData[i++] = new LocationIp(IpBegin, iLatitude, iLongitude);
            if (i % (NBR_IP_ADDRESSES/10) ==0){
                std::cout<< i /(NBR_IP_ADDRESSES/100) <<"% == " <<std::flush;
            }
        }
        std::cout<<"...  done" <<std::endl;

        return importedData;
    }
    return NULL;
}