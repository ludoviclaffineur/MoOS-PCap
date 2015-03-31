//#include "Grid.h"
#include "WebSocketServer.h"
#include "server.hpp"
#include "FileSystem.h"




using namespace mapping;
using namespace view;



int main(int argc, const char * argv[])
{
        std::stringstream ss;
        WebSocketServer* theWebSocketServer = new WebSocketServer(9002);
        utils::FileSystem::SetCurrentPath(argv);
        ss << utils::FileSystem::GetCurrentPath() << "/www";

        std::cout<<"string stream"<<ss.str()<<std::endl;
        theWebSocketServer->start();

        std::cout<<"Lauching Web server... you can access at http://127.0.0.1"<<std::endl;
        http::server::server s("0.0.0.0", "8080", ss.str());
        s.run();
        std::cout<<"\nShuting down Web server..."<<std::endl;
        //delete theCaptureDevice;
        // delete theGrid;
        //delete theGeneticAlgorithm;
        theWebSocketServer->sendStopMessage();
        delete theWebSocketServer;
        //theGrid = new Grid();
        //ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(theGrid);
}