//
//  CopperlanHandler.h
//  MOOS
//
//  Created by Ludovic Laffineur on 22/07/15.
//
//

#ifndef __MOOS__CopperlanHandler__
#define __MOOS__CopperlanHandler__

#include "Chai.h"
#include "OutputsHandler.h"
class CopperlanHandler
{
public:
    //====================
    // Constructor/Destructor
    //====================
    CopperlanHandler();
    ~CopperlanHandler();
    //====================
    // Public methods
    //====================
    bool Initialize();
    void Terminate();
    void addOutput(std::string name);
    //void AddOutput(CHOutput o);
    void removeOutput(std::string name);
    void sendWithOutputName(std::string name, float value);
    void sendData();
    void setNameForOutput(std::string oldName, std::string newName);

private:
    //====================
    // Members
    //====================
    CPNS::IOutput* findOutputWithName(std::string name);
    CPNS::ICHAI* m_pCHAI;
    CPNS::IBaseLocalDevice* m_pDevice;
    CPNS::IInput* m_pInput;
    std::vector<CPNS::IOutput*> m_pOutputs;

};

#endif /* defined(__MOOS__CopperlanHandler__) */
