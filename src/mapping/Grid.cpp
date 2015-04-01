//
//  Grid.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"
#include <ctime>

using namespace mapping;

Grid::Grid(){
    mCurrentOutputId = 0;
    mActive=false;
    //mWebSocket = new WebSocketServer(9002);
    //mWebSocket->start();
    mIsMonitored = true;
}

Grid::~Grid(){
    for(int i = 0; i<mInputs.size();i++){
        delete mInputs[i];
    }
    for(int i = 0; i<mOutputs.size();i++){
        delete mOutputs[i];
    }
    for(int i = 0; i<mCells.size();i++){
        delete mCells[i];
    }
    mCells.clear();
    mInputs.clear();
    mOutputs.clear();
    //delete mWebSocket;
}

float* Grid::getCoeffs(){
    float* coeffs = new float[mCells.size()];
    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        coeffs[j] = (*i)->getCoeff();
    }
    return coeffs;
}

void Grid::setCoeffs(float *coeffs){
    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        (*i)->setCoeff(((int)(coeffs[j]*100))/100.0f);
    }

}

void Grid::setCoeffs(float **coeffs){
    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        (*i)->setCoeff(coeffs[j%getNbrInputs()][j/getNbrInputs()]);
    }

}


void Grid::addInput(std::string name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    mInputs.push_back(new Input(name, min, max, xOffset, yOffset, typeOfExtrapolation));
}

void Grid::addInput(Input* i){
    mInputs.push_back(i);
}

void Grid::addOutput(OutputsHandler* o){
    o->setId(mCurrentOutputId++);
    mOutputs.push_back(o);
    addComplementaryCells(o);
}

void Grid::addOutput(int pos, OutputsHandler* o){
    o->setId(mCurrentOutputId++);
    mOutputs.insert(mOutputs.begin()+pos, o);
    addComplementaryCells(pos,o);

}

void Grid::addComplementaryCells(int posOutput, OutputsHandler *o){
    for (int i=0;i< mInputs.size();i++){
        mCells.insert(mCells.begin()+mInputs.size()*posOutput+i, new Cell(mInputs.at(i), o , 0.0));
    }
}

void Grid::addComplementaryCells(OutputsHandler *o){
    for (int i=0;i< mInputs.size();i++){
        addCell(mInputs.at(i)->getName(), o->getName(), 0.0);
    }

}

void Grid::addCell(std::string inputName, std::string outputName, float corrCoeff){
    mCells.push_back(new Cell(getInputWithName(inputName), getOutputWithName(outputName) , corrCoeff));
}

void Grid::compute(){
    if (mIsMonitored){
        //mWebSocket->sendMessage(getInputs());
    }
    if (mActive) {
        std::vector<Cell*>::iterator i;
        //std::cout<<mCells.size();
        for (i= mCells.begin(); i!=mCells.end();i++ ) {
            (*i)->getOutput()->addToValue((*i)->getInput()->getExtrapolatedValue()* (*i)->getCoeff());
            //std::cout<< "Value Output cells "<< (*i)->getCoeff()<<std::endl;
        }
        std::vector<OutputsHandler*>::iterator j;
        for (j= mOutputs.begin(); j!=mOutputs.end();j++ ) {
            (*j)->extrapolate();
            (*j)->sendData(); //COST A MAX
            (*j)->reset();
        }
    }
}
int Grid::getCurrentOutputId(){
    return mCurrentOutputId;
}

Input* Grid::getInputWithName(std::string n){
    std::vector<Input*>::iterator j;
    for (j= mInputs.begin(); j!=mInputs.end();j++ ) {
        if ((*j)->compareName(n)) return (*j);
    }
    return NULL;
}

OutputsHandler* Grid::getOutputWithName(std::string n){
    std::vector<OutputsHandler*>::iterator j;
    for (j= mOutputs.begin(); j!=mOutputs.end();j++ ) {
        if ((*j)->compareName(n)) return (*j);
    }
    return NULL;
}

OutputsHandler* Grid::getOutputWithId(int theId){
    std::vector<OutputsHandler*>::iterator j;
    for (j= mOutputs.begin(); j!=mOutputs.end();j++ )
        if (theId == (*j)->getId()) return (*j);
    return NULL;
}

size_t Grid::getNbrInputs(){
    return mInputs.size();
}

size_t Grid::getNbrOutputs(){
    return mOutputs.size();
}

std::vector<Input*>* Grid::getInputs(){
    return &mInputs;
}

std::vector<OutputsHandler*>* Grid::getOutputs(){
    return &mOutputs;
}

std::vector<Cell*>* Grid::getCells(){
    return &mCells;
}

Cell* Grid::getCellWithName(std::string input, std::string output){
    for(int i=0;i<mCells.size();i++){
        Cell* c = mCells.at(i);
        if (c->getInput()->getName() == input && c->getOutput()->getName() == output){
            return c;
        }
    }
    return  NULL;
}

void Grid::removeOutput(int id){
    std::vector<Cell*>::iterator i;
    for (i= mCells.begin(); i!=mCells.end(); ) {
        if ((*i)->getOutput()->getId() == id) {
            i = mCells.erase(i);
        }
        else{
            i++;
        }
    }
    for (int i =0; i<mOutputs.size(); i++) {
        if (mOutputs.at(i)->getId()== id) {
            mOutputs.erase(mOutputs.begin()+i);
            break;
        }
    }

}

void Grid::testOutput(int identifier){
    OutputsHandler* o = getOutputWithId(identifier);
    o->setValue(0.0);
    o->sendData();
}

