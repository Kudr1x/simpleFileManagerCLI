#ifndef IFILESYSTEMSERVICE_HPP
#define IFILESYSTEMSERVICE_HPP

#include "../domain/FileSystemEntity.hpp"
#include "../domain/DirectoryStats.hpp"
#include <string>
#include <vector>

namespace application {

    class IFileSystemService {
    public:
        virtual ~IFileSystemService() = default;

        [[nodiscard]] virtual std::string getCurrentPath() const = 0;
        [[nodiscard]] virtual std::vector<domain::FileSystemEntity> listDirectory() const = 0;
        virtual bool changeDirectory(const std::string& path) = 0;
        [[nodiscard]] virtual domain::DirectoryStats getDirectoryStats() const = 0;
        virtual domain::FileTypeStats getFileTypeStats() const = 0;

    };

}

#endif
