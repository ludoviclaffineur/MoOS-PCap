   //
//  WebSocketServer.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 8/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "WebSocketServer.h"
#include <boost/thread.hpp>
#include "AppIncludes.h"

#include "Parameter.h"
#include "FileSystem.h"
#include <dirent.h>
/*

|Opcode  | Meaning                             | Reference |
-+--------+-------------------------------------+-----------|
| 0      | Continuation Frame                  | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 1      | Text Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 2      | Binary Frame                        | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 8      | Connection Close Frame              | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 9      | Ping Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 10     | Pong Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|

*/
using namespace view;
using namespace output::midi;
using namespace output;


void WebSocketServer::onMessage(WebSocketServer* ws, websocketpp::connection_hdl hdl, message_ptr msg){
    ws->mConnectionHandler = hdl;
    //std::cout<<"I am HERE" <<std::endl;
    ws->dispatchRequest(msg);

}


WebSocketServer::WebSocketServer(int port){
    //mServer = new server();
    mCaptureDevice =NULL;
    isConfigured = false;
    mTypeOfCaptureDevice = -1;
    mDefaultOutput = -1;
    mListenningPort = port;
    mGrid = new Grid();
    try{
        mServer.set_access_channels(websocketpp::log::alevel::none);
        mServer.clear_access_channels(websocketpp::log::alevel::frame_payload);
        mServer.init_asio();
        mServer.set_reuse_addr(true);

        // Register our message handler
        mServer.set_message_handler(bind(&WebSocketServer::onMessage,this,::_1,::_2));
        mServer.listen(port);
        mServer.start_accept();
    }
    catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (websocketpp::lib::error_code e) {
        std::cout << e.message() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }

    //To be in the main thread...

}



WebSocketServer::~WebSocketServer(){
    sendStopMessage();
    mConnectionHandler.reset();
    mServer.stop();
    pthread_join(mThread, NULL);
}

void WebSocketServer::sendStopMessage(){
    using boost::property_tree::ptree;
    ptree action;
    action.put("action","stopConnection");
    sendMessage(action);
}

void WebSocketServer::dispatchRequest(message_ptr msg){
    using boost::property_tree::ptree;
    ptree pt;

    try{
        std::stringstream ss;
        std::cout<< msg->get_raw_payload().c_str() <<std::endl;
        ss<<msg->get_raw_payload().c_str();
        read_json(ss, pt);
    }
    catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    if (strcmp(pt.get<std::string>("action").c_str(), "init") == 0) {
        sendInit();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setCaptureDevice") == 0) {
        //sendStopMessage();
        setCaptureDevice(pt.get<int>("parameters.id"));

    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setConfigurationPcap")==0){
        setConfigurationPcap(pt.get<int>("parameters.id"));
        sendOutputList();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setDefaultOutput")==0){
        setDefaultOutput(pt.get<int>("parameters.id"));

    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "sendWeight")==0){
        setWeightForCell(pt.get<std::string>("parameters.inputName"),
                         pt.get<std::string>("parameters.outputName"),
                         pt.get<float>("parameters.weight"));
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "trig")==0){
        trigGrid();
        std::cout<< "TRIG"<< std::endl;
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setMidiPort")==0){
        setMidiPort(pt.get<int>("parameters.id"));
        sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setRow")==0){
        setRow(pt.get<int>("parameters"));
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "setOutput")==0){
        setOutput(pt.get_child("parameters"));
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "getSavedFiles")==0){
          sendSavedFiles();
           // loadXml();

            //
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "loadXml")==0){
          loadXml(pt.get<std::string>("parameters.filename"));
          sendGrid();

    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "saveState")==0){
        saveToXml(pt.get<std::string>("parameters.filename"));
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "addOutput")==0){
        addOutput();
        sendGrid();
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "removeOutput")==0){
        removeOutput(pt.get<int>("parameters.identifier"));
        //sendGrid();
    }
    else if (strcmp(pt.get<std::string>("action").c_str(), "testOutput")==0){
        testOutput(pt.get<int>("parameters.identifier"));
        //sendGrid();
    }
}

void WebSocketServer::setOutput(boost::property_tree::ptree pt){
    using boost::property_tree::ptree;
    std::vector<std::string> paramList;
    std::cout<< pt.get<std::string>("Name").c_str() <<std::endl;
    //int outputType = pt.get<int>("OutputType");
    for (const std::pair<std::string, ptree> &p : pt){
        paramList.push_back(p.first);
        paramList.push_back(p.second.get_value<std::string>());
    }
    mGrid->getOutputWithId(pt.get<int>("identifier"))->setParameters(paramList);
    sendGrid();
}

void WebSocketServer::setWeightForCell(std::string inputName, std::string outputName, float weight){
    mGrid->getCellWithName(inputName, outputName)->setCoeff(weight);
}

void WebSocketServer::setRow(int identifier){
    mCaptureDevice->setRow(identifier);
    sendDescription();
}

void WebSocketServer::setDefaultOutput(int identifier){
    if(mDefaultOutput == -1){
        mDefaultOutput = identifier;
        switch (mDefaultOutput) {
            case CONSTANCES::OSC:{
                mGrid->addOutput(new OscHandler("TEST","127.0.0.1","20000", "/osc", "f" ));
                mGrid->addOutput(new OscHandler("TEST2","127.0.0.1","20000", "/osc1", "f" ));
                sendGrid();
                break;
            }
            case CONSTANCES::MIDI:{
                mMidiHandler = new MidiHandler();
                sendMidiPorts();
                break;

            }
            case CONSTANCES::GRANULAR_SYNTH:{
                mGranularSynth = new GranularSyntheziser();
                mGrid->addOutput(new GSDurationHandler(mGranularSynth));
                mGrid->addOutput(new GSOverlapHandler(mGranularSynth));
                mGrid->addOutput(new GSBlankHandler(mGranularSynth));
                mGrid->addOutput(new GSReverbDecayHandler(mGranularSynth));
                mGrid->addOutput(new GSReverbDelayHandler(mGranularSynth));
                mGrid->addOutput(new GSLowPassCutoffHandler(mGranularSynth));
                mGrid->addOutput(new GSInitPositionHandler(mGranularSynth));
                sendGrid();
                break;

            }
            case CONSTANCES::COPPERLAN:{
                mCopperlanHander = new CopperlanHandler();
                CHDataTransferMessageHandler* CHDTM = new CHDataTransferMessageHandler("Output2", mCopperlanHander);
                mGrid->addOutput(CHDTM);
                mCopperlanHander->addOutput("Output2");
                sendGrid();
                break;

            }
            default:
                break;
        }
        mGrid->switchActive();
    }
}

void WebSocketServer::sendMidiPorts(){
    using boost::property_tree::ptree;
    std::string* ports = mMidiHandler->getPorts();
    int nbrPorts = mMidiHandler->getPortsNbr();
    ptree midiports,parameters, action;
    for (int i =0 ; i<nbrPorts; i++) {
        std::stringstream ss;
        ss<<i;
        parameters.put(ss.str(),ports[i]);
    }
    action.put("action", "setOutputConfig");
    action.put_child("parameters", parameters);
    sendMessage(action);
}

void WebSocketServer::setMidiPort(int identifier){
    mMidiHandler->setMidiPort(identifier);
    mMidiNoteHandler = new MidiNoteHandler(mMidiHandler);
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,1, "Noise"));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,5, "Feedback"));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,6, "FreqEq", 131,0));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,2, "Resonnance",80,127));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,4, "Insert"));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,3, "Modulation"));
    // mGrid->addOutput(new MidiControlChange(mMidiHandler,7, "EqualBoost",0,64));
    mGrid->addOutput(new MidiNoteVelocityHandler(mMidiNoteHandler));
    mGrid->addOutput(new MidiNoteKeyHandler(mMidiNoteHandler));
    mGrid->addOutput(new MidiNoteDurationHandler(mMidiNoteHandler));
}

void WebSocketServer::trigGrid(){
    mCaptureDevice->trig();
    sendDescription();
}

void WebSocketServer::sendDescription(){
    using boost::property_tree::ptree;
    ptree inputs,parameters, action;
    action.put("action", "setDescription");
    action.put("parameters", mCaptureDevice->getDescription());
    sendMessage(action);
}

void WebSocketServer::addOutput(){
    static int currentValue=0;
    switch (mDefaultOutput) {

        case CONSTANCES::OSC:{
            std::stringstream ss;
            ss << "NewOSC" <<currentValue ++;
            mGrid->addOutput(new OscHandler(ss.str(),"127.0.0.1","20000", "/osc", "f" ));
            sendGrid();
            break;
        }
        case CONSTANCES::MIDI:{

            std::stringstream ss;
            ss << "NewMidi" <<currentValue ++;
            mGrid->addOutput(mGrid->getOutputs()->size()-3, new MidiControlChange(mMidiHandler,1, ss.str()));
            break;

        }
        case CONSTANCES::GRANULAR_SYNTH:{
        }
        case CONSTANCES::COPPERLAN:{
            std::stringstream ss;
            ss << "NewCopperlan" <<currentValue ++;
            CHDataTransferMessageHandler* CHDTM = new CHDataTransferMessageHandler(ss.str(), mCopperlanHander);
            mGrid->addOutput(CHDTM);
            mCopperlanHander->addOutput(ss.str());

        }
        default:
            break;
    }

}

void WebSocketServer::sendGrid(){
    isConfigured = true;
    using boost::property_tree::ptree;
    ptree inputs,parameters,outputs,weights, action, rowsData;

    outputs = getJsonOutputs();
    inputs = getJsonInputs();
    weights = getJsonWeights();
    rowsData = getJsonRowsData();

    action.put("action", "setGrid");

    parameters.put_child("outputs", outputs);
    parameters.put_child("inputs", inputs);
    parameters.put_child("weights", weights);
    parameters.put("description", mCaptureDevice->getDescription());
    parameters.put_child("rowsData", rowsData);

    action.put_child("parameters", parameters);
    sendMessage(action);
}

boost::property_tree::ptree WebSocketServer::getJsonRowsData(){
    using boost::property_tree::ptree;
    ptree rows;
    std::vector<std::string> descriptions = mCaptureDevice->getAllDescriptions();
    for (int i =0; i<descriptions.size()&& !descriptions[i].empty(); i++) {
        std::stringstream ss;
        ss<<i;
        rows.put(ss.str(), descriptions[i]);
    }
    return rows;
}

boost::property_tree::ptree WebSocketServer::getJsonOutputs(){
    using boost::property_tree::ptree;
    ptree outputsJson;
    ptree currentOutput;
    for (int i=0; i<mGrid->getOutputs()->size(); i++) {
        //ptree currentOutput;
        for (int j = 0 ; j<mGrid->getOutputs()->at(i)->getParameters()->size(); j++) {
            IParameter* p = mGrid->getOutputs()->at(i)->getParameters()->at(j);
            currentOutput.put(p->getName(), p->toString()->str());
        }
        std::stringstream ss;
        ss<<i;
        outputsJson.put_child(ss.str(),currentOutput);
        currentOutput.clear();
    }
    return outputsJson;
}

boost::property_tree::ptree WebSocketServer::getJsonInputs(){
    using boost::property_tree::ptree;
    ptree inputsJson;
    ptree currentInputs;
    for (int i=0; i<mGrid->getInputs()->size(); i++) {
        //ptree currentOutput
        std::stringstream ss;
        ss<<i;
        currentInputs.put(ss.str(), mGrid->getInputs()->at(i)->getName());


        inputsJson.put_child(ss.str(),currentInputs);
        currentInputs.clear();
    }
    return inputsJson;
}

boost::property_tree::ptree WebSocketServer::getJsonWeights(){
    using boost::property_tree::ptree;
    ptree weights;
    ptree currentWeigth;
    for (int i=0; i<mGrid->getCells()->size(); i++) {
        //ptree currentOutput
        std::stringstream ss;
        ss<<i;
        currentWeigth.put("inputName", mGrid->getCells()->at(i)->getInput()->getName());
        currentWeigth.put("outputName", mGrid->getCells()->at(i)->getOutput()->getName());
        currentWeigth.put("weight", mGrid->getCells()->at(i)->getCoeff());

        weights.put_child(ss.str(),currentWeigth);
        currentWeigth.clear();
    }
    return weights;
}

void WebSocketServer::sendOutputList(){
    using boost::property_tree::ptree;
    ptree child, action;
    for (int i =0; i< CONSTANCES::OutputType::Total; i++) {
        std::stringstream ss;
        ss<< i;
        child.put(ss.str() ,CONSTANCES::OutputList[i]);
    }
    action.put("action","set_outputs_list");
    action.put_child("parameters", child);
    sendMessage(action);
}

void WebSocketServer::setConfigurationPcap(int identifier){
    ((PcapHandler*)(mCaptureDevice))->setDev(identifier);
}

void WebSocketServer::setCaptureDevice(int identifier){
    if (mCaptureDevice) {

    }
    if (mCaptureDevice == NULL) {

        mTypeOfCaptureDevice = identifier;
        std::stringstream ss;
        switch (identifier) {
            case CONSTANCES::CaptureDeviceType::PCAP_HANDLER:
                mCaptureDevice = new PcapHandler("!udp port 8000", mGrid);

                break;
            case CONSTANCES::CaptureDeviceType::SERIAL_HANDLER:
               // mCaptureDevice = new SerialHandler(mGrid, "/dev/tty.usbmodem1411", 115200);
                break;
            case CONSTANCES::CaptureDeviceType::LEAPMOTION_HANDLER:
                mCaptureDevice = new LeapMotionHandler(mGrid);
                break;
            case CONSTANCES::CaptureDeviceType::READWAV_HANDLER:
                //mCaptureDevice = new ReadWavFileHandler(mGrid,"/Users/ludoviclaffineur/Documents/MoOS/data/sinus440_1000.wav");
                break;
            case CONSTANCES::CaptureDeviceType::ODBC_HANDLER:

                ss<< "filedsn="<< utils::FileSystem::GetCurrentPath() << "/configuration/psql.dsn";
                mCaptureDevice = new OdbcHandler(mGrid,ss.str().c_str());
                break;
            case CONSTANCES::CaptureDeviceType::VIDEO_OPENCV_HANDLER:
                //mCaptureDevice = new VideoOpenCvHandler(mGrid);
                break;
            default:
                mCaptureDevice = NULL;
                break;
        }
    }
    if (mCaptureDevice) {


        sendConfigurationCaptureDevice();
    }
}

void WebSocketServer::sendConfigurationCaptureDevice(){
    switch (mTypeOfCaptureDevice) {
        case CONSTANCES::CaptureDeviceType::PCAP_HANDLER:
        {
            pcap_if_t* AllDevs =  ((PcapHandler*)(mCaptureDevice))->getAllDevs();
            sendPcapInterfaces(AllDevs);
            break;
        }
        default:
            mCaptureDevice->init();
            sendOutputList();
            break;
    }
}

void WebSocketServer::sendGoToOutputs(){
    using boost::property_tree::ptree;
    ptree child, action;
    action.put("action", "setConfiguration");
    action.put_child("parameters", child);
    sendMessage(action);
}


void WebSocketServer::sendPcapInterfaces(pcap_if_t* interfaces){
    using boost::property_tree::ptree;
    ptree child, action;
    pcap_if_t* d;
    int i=0;
    for( d = interfaces; d; d=d->next){
        std::stringstream ss;
        ss<< i++;
        child.put(ss.str(), d->name);
    }
    action.put("action", "setConfiguration");
    action.put_child("parameters", child);
    sendMessage(action);

}


void WebSocketServer::sendInit(){

    if (isConfigured) {
           // saveToXml();
            //loadXml();
        //SerializeXml* xmlS = new SerializeXml();
            sendGrid();

    }
    else{
        using boost::property_tree::ptree;
        std::cout<< "sendINIt()"<<std::endl;
        if (mCaptureDevice) {
            //delete mCaptureDevice;
        }

        ptree child, action;


        for (int i =0; i< CONSTANCES::CaptureDeviceType::TOTAL; i++) {
            std::stringstream ss;
            ss<< i;
            child.put(ss.str() ,CONSTANCES::CaptureDeviceList[i]);
        }
        action.put("action","capture_device_list");
        action.put_child("parameters", child);
        sendMessage(action);
    }
}

void WebSocketServer::loadXml(std::string filename){
    std::stringstream ss;
    ss<< utils::FileSystem::GetCurrentPath() << "/saves/"<< filename;
        std::ifstream ifs(ss.str());
        assert(ifs.good());
        boost::archive::xml_iarchive ia(ifs);

        ia.template register_type<OscHandler>();
        ia.template register_type<MidiControlChange>();
        ia.template register_type<MidiNoteDurationHandler>();
        ia.template register_type<MidiNoteKeyHandler>();
        ia.template register_type<MidiNoteVelocityHandler>();
        Grid* TheG;
        ia >> boost::serialization::make_nvp("Grid",TheG);
        std::cout << "NOMBRE SORTIES" << TheG->getOutputs()->size() <<std::endl;
        ifs.close();
        //delete mGrid;
        mGrid = TheG;
        mCaptureDevice->setGrid(TheG);
        setOutputsDevices();

        //ia >> TheG;
}

void WebSocketServer::saveToXml(std::string filename){
    std::stringstream ss;
    ss<< utils::FileSystem::GetCurrentPath() << "/saves/" << filename << ".xml";
        std::ofstream ofs(ss.str());
        assert(ofs.good());
        boost::archive::xml_oarchive oa(ofs);
        oa.template register_type<OscHandler>();
        oa.template register_type<MidiControlChange>();
        oa.template register_type<MidiNoteDurationHandler>();
        oa.template register_type<MidiNoteKeyHandler>();
        oa.template register_type<MidiNoteVelocityHandler>();
        oa << boost::serialization::make_nvp("Grid",mGrid);
        ofs.close();

}

void WebSocketServer::setOutputsDevices(){
        if(mDefaultOutput == CONSTANCES::MIDI){
            std::cout<<"OK JE TOURNE et Y A " << mGrid->getOutputs()->size() <<std::endl;
            for(int i = 0; i<mGrid->getOutputs()->size();i++){
                    mGrid->getOutputs()->at(i)->setOutputDevice((void*)mMidiNoteHandler);
                    mGrid->getOutputs()->at(i)->sendData();
            }
            mGrid->switchActive();
        }

}

void WebSocketServer::sendMessage(boost::property_tree::ptree ptree){
    std::stringstream ss;
    write_json(ss, ptree);
    try {
        mServer.send(mConnectionHandler, ss.str(), websocketpp::frame::opcode::TEXT);
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
        << "(" << e.message() << ")" << std::endl;
    }

}


void WebSocketServer::sendMessage(std::vector<Input*>* inputs){
    std::string JsonArray = inputsToJson(inputs);
    try {
        mServer.send(mConnectionHandler, JsonArray, websocketpp::frame::opcode::TEXT);
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
        << "(" << e.message() << ")" << std::endl;
    }

}

std::string WebSocketServer::inputsToJson(std::vector<Input*>* inputs){
    using boost::property_tree::ptree;
    ptree pt;
    ptree children;
    ptree child1, child2, child3;
    for(int i=0; i<inputs->size();i++){
        child1.put(inputs->at(i)->getName(),inputs->at(i)->getExtrapolatedValue());
    }



    pt.put("testkey", "testvalue");
    pt.add_child("InputsDictonnary", child1);
    std::stringstream ss;
    write_json(ss, child1);
    std::string my_string_to_send_somewhere_else = ss.str();
    return my_string_to_send_somewhere_else;
}

void WebSocketServer::start(){
    try{
        pthread_create(&mThread,NULL,WebSocketServer::run,this);
    }
    catch (...) {
        std::cout << "other exception" << std::endl;
    }
}

void* WebSocketServer::run(void* userData){
    WebSocketServer* s = (WebSocketServer*) userData;
    s->mServer.run();
    return nullptr;
}

void WebSocketServer::testOutput(int identifier){
    mGrid->testOutput(identifier);
}

void WebSocketServer::removeOutput(int identifier){
    if(mCopperlanHander){
        OutputsHandler* o = mGrid->getOutputWithId(identifier);
        mCopperlanHander->removeOutput(o->getName());
        
        return;
    }
    mGrid->removeOutput(identifier);

    sendGrid();
}

void WebSocketServer::sendSavedFiles(){
    using namespace std;
    using boost::property_tree::ptree;
    ptree child, action;
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    stringstream ss;

    ss << utils::FileSystem::GetCurrentPath() << "/saves/";
       pdir = opendir (ss.str().c_str()); // "." will refer to the current directory
       struct dirent *pent = NULL;

       // I used the current directory, since this is one which will apply to anyone reading
       // this tutorial~ If I said "C:\\" and you're on Linux, it may get a little confusing!
       if (pdir == NULL) // if pdir wasn't initialised correctly
       { // print an error message and exit the program
           cout << "\nERROR! pdir could not be initialised correctly";
           exit (3);
       } // end if
        int i=0;
       while ((pent = readdir (pdir))) // while there is still something in the directory to list
       {
           if (pent == NULL) // if pent has not been initialised correctly
           { // print an error message, and exit the program
               cout << "\nERROR! pent could not be initialised correctly";
           }
           // otherwise, it was initialised correctly. Let's print it on the console:
           cout << pent->d_name << endl;
           std::stringstream ss2;
           ss2<< i++;
           child.put(ss2.str(), pent->d_name);
       }

       action.put("action", "sendSavedFiles");
       action.put_child("parameters", child);
       sendMessage(action);
}

void WebSocketServer::stop(){

}
