//
//  Cell.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Cell.h"

using namespace mapping;
using namespace output;
Cell::Cell(Input* i, output::OutputsHandler* o, float coeff){
    mInput =i;
    mOutput = o;
    mCoeff = coeff;
}

void Cell:: setCoeff(float coeff){
    if(coeff >=-1 && coeff <=1 ){
        mCoeff = coeff;
    }
}

float Cell::getCoeff(){
    return mCoeff;
}

Input* Cell::getInput(){
    return mInput;
}

OutputsHandler* Cell::getOutput(){
    return mOutput;
}