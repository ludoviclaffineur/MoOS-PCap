//
//  CaptureDevice.h
//  MoOS
//
//  Created by Ludovic Laffineur on 1/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__CaptureDevice__
#define __MoOS__CaptureDevice__

#include <iostream>

#include "Processings.h"
#include "Grid.h"
#include <vector>
#include <string.h>
namespace capture{
using namespace mapping;
//! Capture device class. This class is the mother of all the capture devices

/**
  All class have to inherit this class.
@code
    CaptureDevice = new ChildCapture();
    CaptureDevice->init();
@endcode
*/
class CaptureDevice{
public:

    CaptureDevice():mDescriptions(500){};
    virtual void init() = 0;
    Grid*   getGrid(){
        return mGrid;
    }
    virtual void trig(){};
    virtual ~CaptureDevice(){};
    std::string getDescription(){
        return mDescription;
    }
    std::vector<std::string> getAllDescriptions(){
        return mDescriptions[0];
    }

    void setGrid(Grid*g){
        mGrid = g;
        for(int i=0 ; i<mProcessings.size() ; i++){
            mProcessings[i]->setGrid(g);
        }
    }
    virtual void setRow(int identifier){}
protected:
    std::vector <processing::Processings*> mProcessings;
    Grid*       mGrid;
    std::string mDescription;
    std::vector<std::vector<std::string>> mDescriptions;
    //std::vector<std::vector<std::string>> mSubDescriptions;
    //int mCurrentRow = 0;
};

}
#endif /* defined(__MoOS__CaptureDevice__) */
