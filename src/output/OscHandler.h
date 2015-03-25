//
//  Osc.h
//  MoOS
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__OscHandler__
#define __MoOS__OscHandler__

#include <iostream>
#include <lo/lo.h>
#include "OutputsHandler.h"

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

namespace output{
        class OscHandler : public OutputsHandler{

        public:
            OscHandler();
            //OscHandler(std::string n);
            OscHandler(std::string ipAddress, std::string port);
            OscHandler(std::string n, std::string ipAddress, std::string port, std::string oscAddress, std::string oscTag );
            bool sendData (int paramNumber, float value);
            bool sendData ();

            bool setIpAdress(std::string newIp);
            std::string getIpAdress();

            bool setOscAddress(std::string newOscAddress);
            std::string getOscAddress();

            bool setPort(std::string newPort);
            std::string getPort();

            void setParameters(std::vector<std::string> ParameterList);
            bool setOscTag(std::string newOscTag);
            std::string getOscTag();
            OscHandler(std::string n, std::string ipAddress, std::string port, std::string oscAddress, std::string oscTag , int idController, float min, float max);
            ~OscHandler();

        private:
            lo_address mDistant;
            std::string mIpAddress;
            std::string mPort;
            std::string mOscAddress;
            std::string mOscTag;
            int mIdController;
            bool setTabChar(char** newOne, const char** oldOne);

            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {

                ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this));
                ar & boost::serialization::make_nvp("IdController",mIdController)
                   & boost::serialization::make_nvp("IpAdress",mIpAddress)
                   & boost::serialization::make_nvp("Port",mPort)
                   & boost::serialization::make_nvp("OscTag",mOscTag)
                   & boost::serialization::make_nvp("OscAddress",mOscAddress);
            }

        };
}



#endif /* defined(__MoOS__Osc__) */