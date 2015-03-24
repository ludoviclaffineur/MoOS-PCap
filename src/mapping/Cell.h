//
//  Cell.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__Cell__
#define __MoOS__Cell__

#include <iostream>
#include "Input.h"
#include "OutputsHandler.h"
namespace mapping{
        using namespace input;
        class Cell{

        public:
            Cell(Input* i, output::OutputsHandler* o, float coeff);

            void                setCoeff(float coeff);
            float               getCoeff();
            Input*              getInput();
            output::OutputsHandler*     getOutput();

        private:
            float           mCoeff;
            Input*          mInput;
            output::OutputsHandler* mOutput;
        };
}


#endif /* defined(__MoOS__Cell__) */