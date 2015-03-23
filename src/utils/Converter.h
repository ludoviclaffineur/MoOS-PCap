//
//  converter.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 28/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __libpcapTest__converter__
#define __libpcapTest__converter__

#include <iostream>

class Converter{

public:
    enum TypeOfExtrapolation {
        LINEAR      = 1,
        LOGARITHMIC = 2,
        EXPONENTIAL = 3
    };
    Converter();
    Converter(Converter * c);
    Converter(int typeOfExtrapolation);
    Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax);
    Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax, float xOffset, float yOffset);

    float   extrapolate(float inputValue);
    void    setDModifier(float d);
    void    setCModifier(float c);
    void    test();
    void    setYMin(int YMin);
    void    setYMax(int YMax);

private:
    float   exponential(float inputValue);
    float   linear(float inputValue);
    float   logarithmic(float inputValue);
    
    int     mCurrentExtrapolation;
    float   mXMaxValue;
    float   mXMinValue;
    float   mYMaxValue;
    float   mYMinValue;
    float   mXOffset;
    float   mYOffset;
};

#endif /* defined(__libpcapTest__converter__) */