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

#include <boost/serialization/nvp.hpp>

namespace utils{
namespace converter{
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
            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & boost::serialization::make_nvp("XMaxValue", mXMaxValue)
                   & boost::serialization::make_nvp("XMinValue", mXMinValue)
                   & boost::serialization::make_nvp("YMaxValue", mYMaxValue)
                   & boost::serialization::make_nvp("YMinValue", mYMinValue)
                   & boost::serialization::make_nvp("CurrentExtrapolation", mCurrentExtrapolation)
                   & boost::serialization::make_nvp("XOffset", mXOffset)
                   & boost::serialization::make_nvp("YOffset", mYOffset);
            }
        };

}
}


#endif /* defined(__libpcapTest__converter__) */