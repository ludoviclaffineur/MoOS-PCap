//
//  OutputsHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OutputsHandler.h"
#include <string.h>

using namespace output;

OutputsHandler::OutputsHandler(){
    mValueBeforeSending = 0;
}

OutputsHandler::OutputsHandler(const char* n){
    mName = new char [strlen(n) + 1];
    strcpy(mName, n);
    mParameters.push_back(new Parameter<char*>("Name", &mName));
    mParameters.push_back(new Parameter<int>("Identifier", &mId));
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 1.0);
}

OutputsHandler::OutputsHandler(const char* n, float min, float max){
    mName = new char [strlen(n) + 1];
    strcpy(mName, n);
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 1.0);
    //mConverter.test();
    mParameters.push_back(new Parameter<char*>("Name", &mName));
    mParameters.push_back(new Parameter<int>("Identifier", &mId));

}

bool OutputsHandler::compareName(const char *n){
    return (strcmp(n, mName)==0);
}

void OutputsHandler::addToValue(float a){
    mValueBeforeSending =  mValueBeforeSending+ a;
    //std::cout<< mValueBeforeSending <<std::endl;
}

void OutputsHandler::extrapolate(){
    if (mValueBeforeSending > 1 ) {
        mValueBeforeSending = 1.0;
    }
    else if (mValueBeforeSending <0.0){
        mValueBeforeSending = 0.0;
    }
    mValueBeforeSending = mConverter->extrapolate(mValueBeforeSending);
    //std::cout<< mValueBeforeSending <<std::endl;

}

void OutputsHandler::setValue(float newValue){
    mValueBeforeSending = mConverter->extrapolate(newValue);

}

void OutputsHandler::reset(){
    mValueBeforeSending = 0;
}

OutputsHandler::~OutputsHandler(){
    delete mName;
    delete mConverter;
}


const char* OutputsHandler::getName(){
    return mName;
}

void OutputsHandler::setName(const char *n){
    if (mName) {
        delete mName;
    }
    //std::cout<<n <<" length " << strlen(n) << std::endl;
    mName = new char [strlen(n) + 1];
    strcpy(mName, n);
}

int OutputsHandler::getId(){
    return mId;
}

void OutputsHandler::setId(int newId){
    mId = newId;
}
std::vector<IParameter*>* OutputsHandler::getParameters(){
    return &mParameters;
}

int OutputsHandler::    getOuputType(){
    return mOutputType;
}
