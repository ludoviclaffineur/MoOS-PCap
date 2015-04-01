    //
//  Grid.h
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__Grid__
#define __MoOS__Grid__

#include <iostream>
#include "Input.h"
#include "OutputsHandler.h"
#include "Cell.h"
#include <vector>
// archives Boost

#include <iostream>
#include <fstream>

#include <boost/serialization/nvp.hpp>

#include <boost/serialization/assume_abstract.hpp>

// pour la sérialisation de std::vector
#include <boost/serialization/vector.hpp>

//#include "WebSocketServer.h"
namespace mapping{
        using namespace output;
        using namespace input;
        class Grid{

        public:
            Grid();
            ~Grid();
            void    addComplementaryCells(OutputsHandler* o);
            void    addComplementaryCells(int posOutput, OutputsHandler* o);
            void    addInput(Input* i);
            void    addInput(std::string Name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation);
            void    addOutput(OutputsHandler* o);
            void    addOutput(int pos, OutputsHandler* o);
            void    addCell(std::string inputName,std::string outputName, float corrCoeff);

            void    compute();
            Input*  getInputWithName(std::string n);
            OutputsHandler* getOutputWithName(std::string n);
            OutputsHandler* getOutputWithId(int theId);
            std::vector<Input*>* getInputs();
            size_t  getNbrInputs();
            size_t  getNbrOutputs();
            std::vector<OutputsHandler*>* getOutputs();
            std::vector<Cell*>* getCells();
            Cell*   getCellWithName(std::string input, std::string output);
            int     getCurrentOutputId();
            void    removeOutput(int id);
            float*  getCoeffs();
            void    setCoeffs(float* coeffs);
            void    setCoeffs(float **coeffs);
            void    switchActive(){
                mActive = !mActive;
            }
            void testOutput(int identifier);

            //WebSocketServer* getWebSocketServer(){
              //  return mWebSocket;
            //}

        private:
            int mCurrentOutputId;
            std::vector <Input*> mInputs;
            std::vector <OutputsHandler*> mOutputs;
            std::vector <Cell*>  mCells;
            bool mActive;
            bool mIsMonitored;
            //WebSocketServer* mWebSocket;
            friend class boost::serialization::access;
            //friend std::ostream & operator<<(std::ostream &os, Grid &g);
            template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & boost::serialization::make_nvp("Inputs",mInputs)
                   & boost::serialization::make_nvp("Outputs", mOutputs)
                   & boost::serialization::make_nvp("Cells", mCells);
            }
        };

}


#endif /* defined(__MoOS__Grid__) */