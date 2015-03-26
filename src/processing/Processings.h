//
//  Processings.h
//  MoOS
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__Processings__
#define __MoOS__Processings__

//! Mother Class of all the processings
#include "Grid.h"
namespace processing{


class Processings{

public:
    //! activate the processing or not
    virtual void setActive(bool active) = 0;
    //! return if the processing is active
    bool isActive(){return mActive;}
    //! where the process will take part
    virtual void process (void* vdata) = 0;
    virtual void setGrid(mapping::Grid* g){}; //BETTER TO PUT IN ANOTHER CLASS MAKING THIS PURELY PROCESS.

protected:
    //! boolean to active or desactive processing
    bool mActive;
    //! permit user to give setter for computed values of the processing
    //! @param nbrSetter amount of setters,
    //! @param ... setters
    virtual void setSetter(int nbrSetter,...) = 0;
};


}

#endif /* defined(__MoOS__Processings__) */
