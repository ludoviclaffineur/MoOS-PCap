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
            OutputsHandler(std::string n);
            OutputsHandler(std::string n, float min, float max);
            virtual ~OutputsHandler();
            void    setId(int newId);
            int     getId();
            void    addToValue(float a);
            bool    compareName (std::string n);
            void    extrapolate();
            std::string getName();
            int     getOuputType();
            void setName(std::string n);
            std::vector<IParameter*>* getParameters();
            void    reset();
            void setValue(float newValue);
            float getValue(){
                return mValueBeforeSending;
            };
            virtual bool sendData (int paramNumber, float value){return false;};
            virtual bool sendData (){return false;};
            virtual void setParameters(std::vector<std::string> ParameterList)=0;
            virtual void setOutputDevice(void* device){};
        protected:

            int     mId;
            int     mOutputType;
            float   mValueBeforeSending;
            int     mParamNumber; //pas topitop
            std::string mName;
            Converter* mConverter;
            std::vector<IParameter*> mParameters;

            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                    //ar.template register_type<IParameter>();
                ar & boost::serialization::make_nvp("name",mName)
                   & boost::serialization::make_nvp("identifier",mId)
                   & boost::serialization::make_nvp("outputType",mOutputType)
                   & boost::serialization::make_nvp("Converter",mConverter);
            }
        };
}



#endif /* defined(__MoOS__OutputsHandler__) */