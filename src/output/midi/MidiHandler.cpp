//
//  MidiHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiHandler.h"

using namespace output::midi;
/*
 Command	Meaning	# parameters	param 1	param 2
 0x80	Note-off	2	key	velocity
 0x90	Note-on	2	key	veolcity
 0xA0	Aftertouch	2	key	touch
 0xB0	Continuous controller	2	controller #	controller value
 0xC0	Patch change	2	instrument #
 0xD0	Channel Pressure	1	pressure
 0xE0	Pitch bend	2	lsb (7 bits)	msb (7 bits)
 0xF0	(non-musical commands)
*/


MidiHandler::MidiHandler(){

    // Check inputs.
    // RtMidiOut constructor
    try {
        mMidiOut = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    //selectPort();
}

MidiHandler::~MidiHandler(){
    //delete mMidiOut;
}

void MidiHandler::selectPort(){
    int nPorts;
    std::string portName;

    nPorts = mMidiOut->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = mMidiOut->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            //~MidiHandler();
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n' << "Select the port to conect: ";
    int selectedPort = 0;
    std::cin >> selectedPort;
    mMidiOut->openPort( selectedPort-1 );
}

void MidiHandler::setMidiPort(int identifier ){
    mMidiOut->openPort( identifier );
}

std::string* MidiHandler::getPorts(){
    int nPorts;

    nPorts = mMidiOut->getPortCount();
    std::string* portName = new std::string[nPorts];
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName[i] = mMidiOut->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            //~MidiHandler();
        }

    }
    return portName;
}

int MidiHandler::getPortsNbr(){
    return mMidiOut->getPortCount();
}

void MidiHandler::sendNoteOn(unsigned char key, unsigned char velocity){
    std::vector<unsigned char> messages (3);
    messages[0] = NOTE_ON;
    messages[1] = key;
    messages[2] = velocity;
    mMidiOut->sendMessage( &messages );
}

void MidiHandler::sendNoteOff(unsigned char key, unsigned char velocity){
    std::vector<unsigned char> messages (3);
    messages[0] = NOTE_OFF;
    messages[1] = key;
    messages[2] = velocity;
    mMidiOut->sendMessage( &messages );
}


void MidiHandler::sendControlChange(unsigned char controller, unsigned char controllerValue){
    std::vector<unsigned char> messages (3);
    messages[0] = CONTINUOUS_CONTROLLER;
    messages[1] = controller;
    messages[2] = controllerValue;
    mMidiOut->sendMessage( &messages );
}
