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

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <string>
#include <sstream>

namespace mapping{
        using namespace input;
        class Cell{

        public:
            Cell(){};
            Cell(Input* i, output::OutputsHandler* o, float coeff);

            void                setCoeff(float coeff);
            float               getCoeff();
            Input*              getInput();
            output::OutputsHandler*     getOutput();

        private:
            float           mCoeff;
            Input*          mInput;
            output::OutputsHandler* mOutput;
            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & boost::serialization::make_nvp("Input",mInput)
                   & boost::serialization::make_nvp("Output", mOutput)
                   & boost::serialization::make_nvp("weight", mCoeff);
            }
        };
}


#endif /* defined(__MoOS__Cell__) */