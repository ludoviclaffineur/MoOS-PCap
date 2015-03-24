//
//  Osc.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OscHandler.h"
#include <string.h>
#include <algorithm>
#include "AppIncludes.h"

using namespace output;

OscHandler::OscHandler(): OutputsHandler("OscNew",0,1){
    mDistant = lo_address_new("127.0.0.1", "57120");
    mParamNumber = 0;
    mValueBeforeSending = 0;

    mIpAddress = new char [strlen("127.0.0.1") + 1];
    strcpy(mIpAddress, "127.0.0.1");

    mPort = new char [strlen("20000") + 1];
    strcpy(mPort, "20000");

    mOscAddress = new char [strlen("/UNDIFINED") + 1];
    strcpy(mOscAddress, "/UNDIFINED");

    mOscTag = new char [strlen("f") + 1];
    strcpy(mOscTag , "f");
    mIdController = -1;
    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<char*>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<char*>("Port", &mPort));
    mParameters.push_back(new Parameter<char*>("OscAddressPattern", &mOscAddress));
}

OscHandler::OscHandler(std::string n, const char* ipAddress, const char* port, const char* oscAddress, const char* oscTag ):OutputsHandler(n,0,1){

    mIpAddress = new char [strlen(ipAddress) + 1];
    strcpy(mIpAddress, ipAddress);

    mPort = new char [strlen(port) + 1];
    strcpy(mPort, port);

    mOscAddress = new char [strlen(oscAddress) + 1];
    strcpy(mOscAddress, oscAddress);

    mOscTag = new char [strlen(oscTag) + 1];
    strcpy(mOscTag , oscTag);

    mDistant = lo_address_new(mIpAddress, mPort);
    mParamNumber = 0;
    //mValueBeforeSending = 0;
    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<char*>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<char*>("Port", &mPort));
    mParameters.push_back(new Parameter<char*>("OscAddressPattern", &mOscAddress));
    mValueBeforeSending = 0;
    mIdController = -1;
    //mParameters.push_back(new Parameter<char**>("OscTag", &mOscTag));
    //mParameters.push_back(new Parameter<int*>("TagIValue", &mParamNumber));
    //mParameters.push_back(new Parameter<int*>("Type", &mOutputType));

}

OscHandler::OscHandler(std::string n, const char* ipAddress, const char* port, const char* oscAddress, const char* oscTag , int idController, float min, float max):OutputsHandler(n,min,max){
    mIdController = idController;
    mIpAddress = new char [strlen(ipAddress) + 1];
    strcpy(mIpAddress, ipAddress);
    mValueBeforeSending = 0;
    mPort = new char [strlen(port) + 1];
    strcpy(mPort, port);

    mOscAddress = new char [strlen(oscAddress) + 1];
    strcpy(mOscAddress, oscAddress);

    mOscTag = new char [strlen(oscTag) + 1];
    strcpy(mOscTag , oscTag);

    mDistant = lo_address_new(mIpAddress, mPort);
    mParamNumber = 0;
    //mValueBeforeSending = 0;


    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<char*>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<char*>("Port", &mPort));
    mParameters.push_back(new Parameter<char*>("OscAddressPattern", &mOscAddress));
    //mParameters.push_back(new Parameter<char**>("OscTag", &mOscTag));
    //mParameters.push_back(new Parameter<int*>("TagIValue", &mParamNumber));
    //mParameters.push_back(new Parameter<int*>("Type", &mOutputType));

}

OscHandler::OscHandler(const char* ipAddress, const char* port){
    mDistant = lo_address_new(ipAddress, port);
    mParamNumber = 0;
    mValueBeforeSending = 0;
    //mValueBeforeSending = 0;
}

bool OscHandler::sendData(){
    //std::cout<< mName << " Sent value" << mValueBeforeSending<<std::endl;
    if (mIdController == -1){
        //std::cout<<mValueBeforeSending<< std::endl;
        return lo_send(mDistant,mOscAddress, "f",mValueBeforeSending);
    }
    else{
        //printf("%f \n", mValueBeforeSending);
        return lo_send(mDistant,mOscAddress, "if",mIdController,mValueBeforeSending);
    }


}

bool OscHandler::sendData(int paramNumber, float value){

    return lo_send(mDistant,mOscAddress, "f",value);
}

bool OscHandler::setIpAdress(const char* newIp){
    setTabChar(&mIpAddress, &newIp);
    lo_address osc = mDistant;
    //printf("New IpAddress %s \n", mIpAddress);
    mDistant = NULL;
    lo_address_free(osc);
	return mDistant = lo_address_new(mIpAddress, mPort);
}

const char* OscHandler::getIpAdress() const{
    return mIpAddress;
}

bool OscHandler::setOscAddress(const char* newOscAddress){
    return setTabChar(&mOscAddress, &newOscAddress);
}

const char* OscHandler::getOscAddress() const{
    return mOscAddress;
}

bool OscHandler::setPort(const char* newPort){
    setTabChar(&mPort, &newPort);
    lo_address osc = mDistant;
    mDistant = NULL;
    lo_address_free(osc);
	return mDistant = lo_address_new(mIpAddress, mPort);
}

const char* OscHandler::getPort() const{
    return mPort;
}

bool OscHandler::setOscTag(const char* newOscTag){
    return setTabChar(&mOscTag, &newOscTag);
}

const char* OscHandler::getOscTag() const{
    return mOscTag;
}

void OscHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("Identifier")==0) {
            setId(std::atoi(ParameterList.at(i+1).c_str()));
        }
        else if (ParameterList.at(i).compare("IPAddress")==0) {
            setIpAdress(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("Port")==0) {
            setPort(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("OscAddressPattern")==0) {
            std::replace( ParameterList.at(i+1).begin(), ParameterList.at(i+1).end(), ':', '/' );
            setOscAddress(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("TagIValue")==0) {
            mParamNumber = std::atoi(ParameterList.at(i+1).c_str());
        }
    }
}

bool OscHandler::setTabChar(char** target, const char** newValue){
    if(*target){
        delete[] *target;
    }
    //std::cout<< *newValue <<" length " << strlen(*newValue) <<std::endl;
    *target = new char [strlen(*newValue) + 1];
    return(strcpy(*target, *newValue));
}

OscHandler::~OscHandler(){
    //lo_address_free(mDistant);
    delete mOscTag;
    delete mOscAddress;
    delete mIpAddress;
    delete mPort;
}
