//
//  Osc.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OscHandler.h"
#include <string.h>
#include <algorithm>
#include "AppIncludes.h"

using namespace output;

OscHandler::OscHandler():
OutputsHandler("OscNew",0,1),
mIpAddress("127.0.0.1"),
mPort("20000"),
mOscAddress("/UNDIFINED"),
mOscTag("/f")
{
    mDistant = lo_address_new("127.0.0.1", "57120");
    mParamNumber = 0;
    mValueBeforeSending = 0;

    mIdController = -1;
    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<std::string>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<std::string>("Port", &mPort));
    mParameters.push_back(new Parameter<std::string>("OscAddressPattern", &mOscAddress));
}

OscHandler::OscHandler(std::string n, std::string ipAddress, std::string port, std::string oscAddress, std::string oscTag ):

OutputsHandler(n,0,1),
mIpAddress(ipAddress),
mPort(port),
mOscAddress(oscAddress),
mOscTag(oscTag)
{
    mDistant = lo_address_new(mIpAddress.c_str(), mPort.c_str());
    mParamNumber = 0;
    //mValueBeforeSending = 0;
    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<std::string>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<std::string>("Port", &mPort));
    mParameters.push_back(new Parameter<std::string>("OscAddressPattern", &mOscAddress));
    mValueBeforeSending = 0;
    mIdController = -1;
    //mParameters.push_back(new Parameter<char**>("OscTag", &mOscTag));
    //mParameters.push_back(new Parameter<int*>("TagIValue", &mParamNumber));
    //mParameters.push_back(new Parameter<int*>("Type", &mOutputType));

}

OscHandler::OscHandler(std::string n, std::string ipAddress, std::string port, std::string oscAddress, std::string oscTag , int idController, float min, float max):
OutputsHandler(n,min,max),
mIpAddress(ipAddress),
mPort(port),
mOscAddress(oscAddress),
mOscTag(oscTag)
{
    mIdController = idController;

    mValueBeforeSending = 0;



    mDistant = lo_address_new(mIpAddress.c_str(), mPort.c_str());
    mParamNumber = 0;
    //mValueBeforeSending = 0;


    mOutputType = CONSTANCES::OSC;
    mParameters.push_back(new Parameter<std::string>("IPAddress", &mIpAddress));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
    mParameters.push_back(new Parameter<std::string>("Port", &mPort));
    mParameters.push_back(new Parameter<std::string>("OscAddressPattern", &mOscAddress));
    //mParameters.push_back(new Parameter<char**>("OscTag", &mOscTag));
    //mParameters.push_back(new Parameter<int*>("TagIValue", &mParamNumber));
    //mParameters.push_back(new Parameter<int*>("Type", &mOutputType));

}

OscHandler::OscHandler(std::string ipAddress, std::string port){
    mDistant = lo_address_new(ipAddress.c_str(), port.c_str());
    mParamNumber = 0;
    mValueBeforeSending = 0;
    //mValueBeforeSending = 0;
}

bool OscHandler::sendData(){
    //std::cout<< mName << " Sent value" << mValueBeforeSending<<std::endl;
    if (mIdController == -1){
        //std::cout<<mValueBeforeSending<< std::endl;
        return lo_send(mDistant,mOscAddress.c_str(), "f",mValueBeforeSending);
    }
    else{
        //printf("%f \n", mValueBeforeSending);
        return lo_send(mDistant,mOscAddress.c_str(), "if",mIdController,mValueBeforeSending);
    }


}

bool OscHandler::sendData(int paramNumber, float value){

    return lo_send(mDistant,mOscAddress.c_str(), "f",value);
}

bool OscHandler::setIpAdress(std::string newIp){
    mIpAddress = newIp;
    lo_address osc = mDistant;
    //printf("New IpAddress %s \n", mIpAddress);
    mDistant = NULL;
    lo_address_free(osc);
	return mDistant = lo_address_new(mIpAddress.c_str(), mPort.c_str());
}

std::string OscHandler::getIpAdress(){
    return mIpAddress;
}

bool OscHandler::setOscAddress(std::string newOscAddress){
     mOscAddress = newOscAddress;
     return true;
}

std::string OscHandler::getOscAddress(){
    return mOscAddress;
}

bool OscHandler::setPort(std::string newPort){
    mPort = newPort;
    lo_address osc = mDistant;
    mDistant = NULL;
    lo_address_free(osc);
        return mDistant = lo_address_new(mIpAddress.c_str(), mPort.c_str());
}

std::string OscHandler::getPort(){
    return mPort;
}

bool OscHandler::setOscTag(std::string newOscTag){
    mOscTag = newOscTag;
    return true;
}

std::string OscHandler::getOscTag(){
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
}
