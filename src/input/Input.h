//
//  Input.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__Input__
#define __MoOS__Input__

#include <iostream>
#include "Converter.h"
#include "Setter.h"

class Input : public Setter<float>{

public:
    Input();
    Input(const char* name);
    Input(const char* name, Converter c);
    Input(const char* name, float min, float max, int typeOfExtrapolation);
    Input(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation);
    ~Input();

    bool    compareName(const char *n);
    float   getExtrapolatedValue();
    const char* getName();
    void    setValue(float value);

private:
    
    char*   mName;
    Converter* mConverter;
};

#endif /* defined(__MoOS__Input__) */