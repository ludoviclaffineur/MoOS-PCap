//
//  OutputsHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__OutputsHandler__
#define __MoOS__OutputsHandler__

#include <iostream>
#include "Converter.h"
#include <vector>
#include "Parameter.h"
#include <string>
#include <sstream>

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

namespace output{
        using namespace utils::converter;
        class OutputsHandler{


        public:

            OutputsHandler();
            OutputsHandler(const char* n);
            OutputsHandler(const char* n, float min, float max);
            ~OutputsHandler();
            void    setId(int newId);
            int     getId();
            void    addToValue(float a);
            bool    compareName (const char* n);
            void    extrapolate();
            const char* getName();
            int     getOuputType();
            void setName(const char* n);
            std::vector<IParameter*>* getParameters();
            void    reset();
            void setValue(float newValue);
            float getValue(){
                return mValueBeforeSending;
            };
            virtual bool sendData (int paramNumber, float value){return false;};
            virtual bool sendData (){return false;};
            virtual void setParameters(std::vector<std::string> ParameterList)=0;
        protected:

            int     mId;
            int     mOutputType;
            float   mValueBeforeSending;
            int     mParamNumber; //pas topitop
            char*   mName;
            Converter* mConverter;
            std::vector<IParameter*> mParameters;

            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                    std::stringstream ss;
                    std::string s;
                    ss<<mName;
                    ss>>s;
                ar & boost::serialization::make_nvp("name",s)
                   & boost::serialization::make_nvp("Converter",mConverter);
            }
        };
}



#endif /* defined(__MoOS__OutputsHandler__) */