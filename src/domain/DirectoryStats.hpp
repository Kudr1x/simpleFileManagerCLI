#ifndef DIRECTORYSTATS_HPP
#define DIRECTORYSTATS_HPP
#include <map>

namespace domain {

    struct DirectoryStats {
        size_t totalCount;
        size_t fileCount;
        size_t directoryCount;
    };

    struct FileTypeStats {
        std::map<std::string, size_t> extensionCounts;
        size_t totalFiles;
    };

}



#endif
