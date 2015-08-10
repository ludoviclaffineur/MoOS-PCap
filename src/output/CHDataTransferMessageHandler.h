#ifndef __MOOS__CHDataTransferMessageHandler__
#define __MOOS__CHDataTransferMessageHandler__

#include "OutputsHandler.h"
#include "CopperlanHandler.h"

class CHDataTransferMessageHandler: public output::OutputsHandler{
public:
    CHDataTransferMessageHandler(std::string name, CopperlanHandler* CH );
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
private:
    CopperlanHandler* mCopperlanHandler;

};


#endif