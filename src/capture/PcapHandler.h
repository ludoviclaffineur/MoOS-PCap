//
//  PcapHandler.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__PcapHandler__
#define __MoOS__PcapHandler__

#include "CaptureDevice.h"
#include "pcap.h"
#include "Grid.h"
#include "Input.h"
#include "LocationIp.h"
#include "CsvImporter.h"
#include "IpHeaderDefinitions.h"
#include "AppIncludes.h"


#include "Processings.h"
#include "PcapLocationProcessing.h"
#include "PcapIpProcessing.h"
#include "PcapPasswordsProcessing.h"
#include "PcapDnsProcessing.h"
#include "PcapDhcpProcessing.h"
//#include "PcapGrabAndStorePictures.h"
#include "PcapKissProcessing.h"

namespace capture{
        class PcapHandler : public CaptureDevice {

        public:
            PcapHandler();
            ~PcapHandler();
            PcapHandler(char* filter);
            PcapHandler(const char* filter, Grid* g);
            pcap_t* getHandle();
            void    init();
            pcap_if_t* getAllDevs();
            void setDev(int a);


        private:
            void        close(pcap_t* handle);
            void        freeAllDevs(pcap_if_t *alldevs);
            int         findAllDevs(pcap_if_t **alldev, char* errbuff);
            pcap_t*     listAndChooseInterface();
            int         loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);
            int         loopThreading();
            pcap_t*     chooseDev();
            void        listAllDevs();
            pcap_t*     openLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
            pcap_if_t*  mAlldevs;
            char        mErrbuf[PCAP_ERRBUF_SIZE];
            const char* mFilter;
            pcap_t*     mHandle;
            static void* ThreadReceptionPacket (void* ptr);

        };
}



#endif /* defined(__libpcapTest__PcapHandler__) */