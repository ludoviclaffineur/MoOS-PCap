//#include "Grid.h"
#include "WebSocketServer.h"
#include "server.hpp"

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace mapping;
using namespace view;
namespace fs = boost::filesystem;


int main(int argc, const char * argv[])
{
        fs::path full_path( fs::initial_path<fs::path>() );
        full_path = fs::system_complete( fs::path( argv[0] ) );

        std::cout << full_path.parent_path() << std::endl;
        std::stringstream ss;
        WebSocketServer* theWebSocketServer = new WebSocketServer(9002);

        ss << full_path.parent_path().string() << "/www";

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