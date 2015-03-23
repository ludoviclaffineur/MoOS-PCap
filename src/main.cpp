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
        WebSocketServer* theWebSocketServer = new WebSocketServer(9002);
        theWebSocketServer->start();
        std::stringstream ss;
        ss << CURRENT_PATH << "/www";


        std::ofstream ofs("filename.xml");
        assert(ofs.good());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(theGrid);


        std::cout<<"Lauching Web server... you can access at http://127.0.0.1"<<std::endl;
        http::server::server s("0.0.0.0", "80", ss.str());
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