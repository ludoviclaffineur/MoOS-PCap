//
//  PcapPasswordsProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 8/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapPasswordsProcessing.h"
#include <sstream>
#include <string.h>
#include <regex>
using namespace processing::pcap;
PcapPasswordsProcessing::PcapPasswordsProcessing(){

}

void PcapPasswordsProcessing::setActive(bool active){
    mActive = active;
}

void PcapPasswordsProcessing::process(const u_char* data){
    using namespace std;
    std::stringstream ssName;
    string s ( reinterpret_cast<const char*>(data), mLength );
    //string s ("%5Bpassword%5D=35473&");
    //ssName << (char*)data;
    //char* tab = (char*)data;
    int i=0;
    cout <<s<<endl;
    std::smatch m_input;
    std::regex e_input ("password.+=(\\w+)\\&");   // matches words beginning by "sub"


}

void PcapPasswordsProcessing::setLength(int length){
    mLength = length;
}