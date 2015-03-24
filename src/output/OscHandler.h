//
//  Osc.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __libpcapTest__OscHandler__
#define __libpcapTest__OscHandler__

#include <iostream>
#include <lo/lo.h>
#include "OutputsHandler.h"

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

namespace output{
        class OscHandler : public OutputsHandler{

        public:
            OscHandler();
            //OscHandler(const char* n);
            OscHandler(const char* ipAddress, const char* port);
            OscHandler(const char* n, const char* ipAddress, const char* port, const char* oscAddress, const char* oscTag );
            bool sendData (int paramNumber, float value);
            bool sendData ();

            bool setIpAdress(const char* newIp);
            const char* getIpAdress() const;

            bool setOscAddress(const char* newOscAddress);
            const char* getOscAddress() const;

            bool setPort(const char* newPort);
            const char* getPort() const;

            void setParameters(std::vector<std::string> ParameterList);
            bool setOscTag(const char* newOscTag);
            const char* getOscTag() const;
            OscHandler(const char* n, const char* ipAddress, const char* port, const char* oscAddress, const char* oscTag , int idController, float min, float max);
            ~OscHandler();

        private:
            lo_address mDistant;
            char* mIpAddress;
            char* mPort;
            char* mOscAddress;
            char* mOscTag;
            int mIdController;
            bool setTabChar(char** newOne, const char** oldOne);

            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {

                ar & boost::serialization::make_nvp("OutputHandler",boost::serialization::base_object<OutputsHandler>(*this));
                ar & boost::serialization::make_nvp("IdController",mIdController);
            }

        };
}



#endif /* defined(__libpcapTest__Osc__) */