//
//  Input.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Input.h"
#include <string.h>
using namespace input;
Input::Input(){
    mName = new char [1];
}

Input::Input(const char* name):mConverter(){
    mName = new char [strlen(name)+1];
    strcpy(mName, name);
}

Input::Input(const char* name, Converter c){
    mConverter = new Converter (c);
    mName = new char [strlen(name)+1];
    strcpy(mName, name);
}

Input::Input(const char* name, float min, float max, int typeOfExtrapolation){
    mConverter = new Converter(typeOfExtrapolation, min, max, 0.0, 1.0);
    mName = new char [strlen(name)+1];
    strcpy(mName, name);

}

Input::Input(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    mConverter = new Converter(typeOfExtrapolation, min, max, 0.0, 1.0,xOffset, yOffset);
    mName = new char [strlen(name)+1];
    strcpy(mName, name);
    //mConverter.test();
}


bool Input::compareName(const char *n){
    //printf("NameInput : %s \n Name to test : %s \n Result strcmp : %d", _Name, n,strcmp(n, _Name));
    return (strcmp(n, mName)==0);
}

void Input::setValue(float value){
    mValue = mConverter->extrapolate(value);
    //std::cout<<"Converted Value"<< _Value<< std::endl;
}

float Input::getExtrapolatedValue(){
    return mValue;
}

const char* Input::getName(){
    return mName;
}

Input::~Input(){
    delete mName;
    delete mConverter;
}