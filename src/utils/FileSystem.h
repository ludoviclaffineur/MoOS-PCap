#ifndef __MoOS__FileSystem__
#define __MoOS__FileSystem__

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <string>


namespace utils{
    static std::string CurrentPath;
class FileSystem{
public:

    static std::string GetCurrentPath();
    static void SetCurrentPath(const char * argv[]);
private:

};
}
#endif /* defined(__MoOS__CsvRow__) */