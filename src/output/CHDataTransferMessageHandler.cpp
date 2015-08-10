#include "CHDataTransferMessageHandler.h"

using namespace output;

CHDataTransferMessageHandler::CHDataTransferMessageHandler(std::string name, CopperlanHandler* CH): OutputsHandler(name){
    mCopperlanHandler = CH;
}

bool CHDataTransferMessageHandler::sendData(){
    mCopperlanHandler->sendWithOutputName(mName, mValueBeforeSending);
    return true;
}

void CHDataTransferMessageHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            std::string s = OutputsHandler::getName();
            mCopperlanHandler->setNameForOutput(s, ParameterList.at(i+1).c_str());
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
    }
}