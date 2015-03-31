#include "FileSystem.h"

namespace fs = boost::filesystem;

void utils::FileSystem::SetCurrentPath(const char * argv[]){
    fs::path full_path( fs::initial_path<fs::path>() );
    full_path = fs::system_complete( fs::path( argv[0] ) );

    CurrentPath = full_path.parent_path().string();
}


std::string  utils::FileSystem::GetCurrentPath(){
   return CurrentPath;
}