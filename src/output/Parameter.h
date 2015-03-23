//
//  Parameter.h
//  MoOS
//
//  Created by Ludovic Laffineur on 6/02/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__Parameter__
#define __MoOS__Parameter__

#include <iostream>
#include <sstream>

class IParameter{

public:

    virtual std::stringstream* toString()=0;
    const char* getName(){
        return mName;
    }
    ~IParameter(){
        delete mName;
    }

protected:
    char* mName;

};


template<class T> class Parameter : public IParameter{

private:
    const T* mData;

public:
    Parameter(const char* name, const T* data){
        mName = new char [strlen(name) + 1];
        strcpy(mName, name);
        mData = data;
    }

    ~Parameter(){
        delete mData;
    }

    std::stringstream* toString() {
        std::stringstream * stm = new std::stringstream();
        (*stm )<< *mData;
        printf("Impression %s\n", stm->str().c_str());
        //s<<mGrid->getOutputs()->at(i)->getName();
        return stm;
    }
};

#endif /* defined(__MoOS__Parameter__) */
