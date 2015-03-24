#include "Grid.h"
#include "WebSocketServer.h"
#include "server.hpp"

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using namespace mapping;
using namespace view;

int main(int argc, const char * argv[])
{
        Grid* theGrid = new Grid();
        std::stringstream ss;
        std::cout << "YOOOOOO ENTR2ES" << argc <<std::endl;
        WebSocketServer* theWebSocketServer = new WebSocketServer(9002);
        if(argc == 2){
                ss << argv[1];
                std::cout << argv[1] <<std::endl;
        }
        else{
                ss<<".";
        }
        ss << "/www";

        std::cout<<"string stream"<<ss.str()<<std::endl;
        theWebSocketServer->start();

        std::cout<<"Lauching Web server... you can access at http://127.0.0.1"<<std::endl;
        http::server::server s("0.0.0.0", "8080", ss.str());
        s.run();
        std::cout<<"\nShuting down Web server..."<<std::endl;
        //delete theCaptureDevice;
        delete theGrid;
        //delete theGeneticAlgorithm;
        theWebSocketServer->sendStopMessage();
        delete theWebSocketServer;
        //theGrid = new Grid();
        //ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(theGrid);
}