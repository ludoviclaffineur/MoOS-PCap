//
//  Setter.h
//  MoOS
//
//  Created by Ludovic Laffineur on 14/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef MoOS_Setter_h
#define MoOS_Setter_h
template<class T> class Setter{
public:
    virtual void setValue(T t){
        mValue = t;
    }
    virtual T getValue(){
        return mValue;
    }
protected:
    T   mValue;
};

#endif
