//
//  PcapHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "PcapHandler.h"

#include <pthread.h>
#include <iostream>
#include <vector>

//#include "PcapPasswordsProcessing.h"
using namespace capture;

pthread_t capture_thread;
bool running = true;

std::vector<char> unzip(const std::vector<char> compressed)
{


    std::vector<char> decompressed = std::vector<char>();

    /*boost::iostreams::filtering_ostream os;

    os.push(boost::iostreams::gzip_decompressor());
    os.push(boost::iostreams::back_inserter(decompressed));

    boost::iostreams::write(os, &compressed[0], compressed.size());*/

    return decompressed;
}

void* capture::PcapHandler::ThreadReceptionPacket (void* ptr){
    PcapHandler* p = (PcapHandler*) ptr;
//    pthread_setname_np("ThreadPcap");
    //pcap_t* handle = (pcap_t*) ptr;
    struct pcap_pkthdr* header;
    const u_char* data;
    int res;
    while(running){
        res = pcap_next_ex(p->getHandle(), &header, &data);

        if (res >0 && data ){
            const char* c = (const char*) data;
            std::vector<processing::Processings*>::iterator i;

            //PcapPasswordsProcessing* PP = (PcapPasswordsProcessing*)p->mProcessings.back();
            //PP->setLength(header->len);

            for (i= p->mProcessings.begin(); i!=p->mProcessings.end();i++ ) {
                (*i)->process(&data);
            }
            p->getGrid()->compute();
        }
    }
    return NULL;
}


PcapHandler::~PcapHandler(){
    running = false;

    pthread_join(capture_thread, NULL); //waiting that capture_thread finishes
    close(mHandle);
    freeAllDevs(mAlldevs);
}

PcapHandler::PcapHandler(){
    mFilter = NULL;
}

void PcapHandler::init(){
    listAndChooseInterface();
    loopThreading();
}

PcapHandler::PcapHandler(char* filter){
    mFilter = filter;
}

PcapHandler::PcapHandler(const char* filter, Grid* g){
    mFilter = filter;
    mGrid = g;
    mProcessings.push_back(new processing::pcap::PcapLocationProcessing(g));
    mProcessings.push_back(new processing::pcap::PcapIpProcessing(g));
    //mProcessings.push_back(new processing::pcap::PcapDnsProcessing());
    mProcessings.push_back(new processing::pcap::PcapDhcpProcessing(g));
    //mProcessings.push_back(new PcapKissProcessing());
    //mProcessings.push_back(new PcapPasswordsProcessing());
    //mProcessings.push_back(new PcapGrapAndStorePictures());

}

int PcapHandler::findAllDevs(pcap_if_t **alldev , char *errbuf){
#ifdef _WIN32
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, alldev, errbuf) == -1){
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		return -1;
	}
#else
//#elif defined __APPLE__
    if (pcap_findalldevs(alldev, errbuf)==-1){
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return -1;
    }
#endif
    return 3;
}

pcap_t* PcapHandler::listAndChooseInterface(){
    struct bpf_program fcode;
    u_int netmask = 0xffffff00;
    listAllDevs();
    pcap_t* handle =  chooseDev();
    if (mFilter){
        pcap_compile(handle, &fcode, mFilter, 1, netmask);
        pcap_setfilter(handle, &fcode);
    }
    return handle;
}

pcap_if_t* PcapHandler::getAllDevs(){
    findAllDevs(&mAlldevs, mErrbuf);
    return mAlldevs;
}

void PcapHandler::listAllDevs(){
    pcap_if_t* d;
    findAllDevs(&mAlldevs, mErrbuf);
    int i=0;
    for( d = mAlldevs; d; d=d->next){
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}
}

pcap_t* PcapHandler::chooseDev(){
    int a;
    pcap_if_t* selected = mAlldevs;
    std::cout<< "Select your interface :";
    std::cin >> a;
    for (int i = 1; i<a; i++){
        selected = selected->next;
    }
    mHandle = openLive(selected->name, BUFSIZ, 1, 1000, mErrbuf);
	return mHandle;
}

void PcapHandler::setDev(int a){
    pcap_if_t* selected = mAlldevs;
    for (int i = 0; i<a; i++){
        selected = selected->next;
    }
    mHandle = openLive(selected->name, BUFSIZ, 1, 1000, mErrbuf);
    loopThreading();
}

pcap_t* PcapHandler::getHandle(){
    return mHandle;
}

pcap_t* PcapHandler::openLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf){
#ifdef _WIN32
    return pcap_open(device,  // name of the device
                     snaplen,     // portion of the packet to capture.
                     // 65536 grants that the whole packet will be captured on all the MACs.
                     promisc,         // promiscuous mode
                     to_ms,      // read timeout
                     NULL,      // remote authentication
                     errbuf     // error bufferqsdqsdqsd
                     )  ;
#else
//#elif defined __APPLE__
    return(pcap_open_live(device, snaplen, promisc, to_ms, errbuf));
#endif
}

int PcapHandler::loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user){
    return pcap_loop(p, cnt, callback, user);
}

int PcapHandler::loopThreading(){
    pthread_create(&capture_thread, NULL, ThreadReceptionPacket, this);
    return 0;
}

void PcapHandler::close(pcap_t* handle){
    pcap_close(handle);
}

void PcapHandler::freeAllDevs(pcap_if_t *alldevs){
    pcap_freealldevs(alldevs);
}


