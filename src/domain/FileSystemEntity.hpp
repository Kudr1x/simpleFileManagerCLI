#ifndef FILESYSTEMENTITY_HPP
#define FILESYSTEMENTITY_HPP

#include <string>

namespace domain {

    enum class EntityType {
        File,
        Directory
    };

    struct FileSystemEntity {
        std::string name;
        EntityType type;
    };

}

#endif
