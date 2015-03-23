//
//  converter.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 28/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Converter.h"
#include <math.h>
#include <string.h>

Converter::Converter(){}

Converter::Converter(int typeOfExtrapolation){
    mCurrentExtrapolation = typeOfExtrapolation;
	mXMaxValue = 0;
    mXMinValue = 6;
    mYMaxValue = 0;
    mYMinValue = 1;
	mYOffset = -3;
	mXOffset = -1;
}

Converter::Converter(Converter * c){
    memcpy(this, c, sizeof(Converter));
}

Converter::Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax){
    mCurrentExtrapolation = typeOfExtrapolation;
    mXMaxValue = xmax;
    mXMinValue = xmin;
    mYMaxValue = ymax;
    mYMinValue = ymin;
    mYOffset = 0;
	mXOffset = 0;
}

Converter::Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax, float xOffset, float yOffset){
    mCurrentExtrapolation = typeOfExtrapolation;
    mXMaxValue = xmax;
    mXMinValue = xmin;
    mYMaxValue = ymax;
    mYMinValue = ymin;
    mYOffset = yOffset;
	mXOffset = xOffset;
}

float Converter::extrapolate(float inputValue){
    switch (mCurrentExtrapolation) {
        case LINEAR:
            return linear(inputValue);
            break;
        case EXPONENTIAL:
            return exponential(inputValue);
            break;
        case LOGARITHMIC:
            return logarithmic(inputValue);
            break;
        default:
            return -1;
    }
}

float Converter::linear(float inputValue){
    float beta = mYMinValue - (mXMinValue*(mYMaxValue-mYMinValue)/(mXMaxValue-mXMinValue));
    float alpha =(mYMaxValue-mYMinValue)/(mXMaxValue-mXMinValue);
    return (alpha*inputValue + beta);
}

float Converter::exponential(float inputValue){
    float b = log((mYMinValue-mXOffset)/(mYMaxValue-mXOffset))/(mXMinValue-mXMaxValue);
    float a = (mYMinValue-mXOffset)/expf(b*mXMinValue-mYOffset);
    //std::cout<<a<<" " << b<< std::endl;
    return (a*expf((inputValue-mYOffset)*b)+mXOffset);
}

float Converter::logarithmic(float inputValue){
    float b = (mYMinValue-mYMaxValue)/log((mXMinValue-mYOffset)/(mXMaxValue-mYOffset));
    float a = expf((mYMinValue-mXOffset)/b)/(mXMinValue-mYOffset);
    //std::cout<<a<<" " << b<< std::endl;
    return ( b*log(a*(inputValue-mYOffset))+mXOffset);
}

void Converter::setDModifier(float d){
    mXOffset = d;
}

void Converter::setCModifier(float c){
    mYOffset = c;
}

void Converter::test(){
    float increment = (mXMaxValue-mXMinValue) / 100.0;
    for (int i = 0; i<100; i++) {

        std::cout<<mXMinValue + i*increment<<" \t"<< extrapolate(mXMinValue + i*increment) <<std::endl;

    }
}

void Converter::setYMin(int YMin){
    mYMinValue = YMin;
}

void Converter::setYMax(int YMax){
    mYMaxValue = YMax;
}
