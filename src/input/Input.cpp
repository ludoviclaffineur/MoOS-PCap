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
}

Input::Input(std::string name): mName(name){
}

Input::Input(std::string name, Converter c): mName(name){
    mConverter = new Converter (c);
}

Input::Input(std::string name, float min, float max, int typeOfExtrapolation): mName(name){
    mConverter = new Converter(typeOfExtrapolation, min, max, 0.0, 1.0);
}

Input::Input(std::string name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation): mName(name){
    mConverter = new Converter(typeOfExtrapolation, min, max, 0.0, 1.0,xOffset, yOffset);
    //mConverter.test();
}


bool Input::compareName(std::string n){

    //printf("NameInput : %s \n Name to test : %s \n Result strcmp : %d", _Name, n,strcmp(n, _Name));
    return (mName.compare(n)==0);
}

void Input::setValue(float value){
    mValue = mConverter->extrapolate(value);
    if(mValue>1){
        mValue = 1;
    }
    if(mValue < 0){
        mValue = 0;
    }
}

float Input::getExtrapolatedValue(){
    return mValue;
}

std::string Input::getName(){
    return mName;
}

Input::~Input(){
    delete mConverter;
}