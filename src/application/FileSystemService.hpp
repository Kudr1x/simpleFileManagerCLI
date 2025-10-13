#ifndef FILESYSTEMSERVICE_HPP
#define FILESYSTEMSERVICE_HPP

#include "IFileSystemService.hpp"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

namespace application {

class FileSystemService : public IFileSystemService {
private:
    fs::path currentPath;

public:
    FileSystemService() : currentPath(fs::current_path()) {}

    [[nodiscard]] std::string getCurrentPath() const override {
        return currentPath.string();
    }

    [[nodiscard]] std::vector<domain::FileSystemEntity> listDirectory() const override {
        std::vector<domain::FileSystemEntity> entities;
        
        try {
            for (const auto& entry : fs::directory_iterator(currentPath)) {
                domain::FileSystemEntity entity;
                entity.name = entry.path().filename().string();
                entity.type = entry.is_directory() ? 
                    domain::EntityType::Directory : 
                    domain::EntityType::File;
                entities.push_back(entity);
            }
            
            std::sort(entities.begin(), entities.end(), 
                [](const auto& a, const auto& b) {
                    if (a.type != b.type) {
                        return a.type == domain::EntityType::Directory;
                    }
                    return a.name < b.name;
                });
        } catch (const fs::filesystem_error&) {

        }
        
        return entities;
    }

    bool changeDirectory(const std::string& path) override {
        try {
            fs::path newPath;
            
            if (fs::path(path).is_absolute()) {
                newPath = fs::path(path);
            } else {
                newPath = currentPath / path;
            }
            
            newPath = fs::canonical(newPath);
            
            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                currentPath = newPath;
                return true;
            }
        } catch (const fs::filesystem_error&) {
            return false;
        }
        
        return false;
    }

    [[nodiscard]] domain::DirectoryStats getDirectoryStats() const override {
        domain::DirectoryStats stats{0, 0, 0};
        
        try {
            for (const auto& entry : fs::directory_iterator(currentPath)) {
                stats.totalCount++;
                if (entry.is_directory()) {
                    stats.directoryCount++;
                } else if (entry.is_regular_file()) {
                    stats.fileCount++;
                }
            }
        } catch (const fs::filesystem_error&) {

        }
        
        return stats;
    }

    [[nodiscard]] domain::FileTypeStats getFileTypeStats() const override {
        domain::FileTypeStats stats;
        stats.totalFiles = 0;

        try {
            for (const auto& entry : fs::directory_iterator(currentPath)) {
                if (entry.is_regular_file()) {
                    std::string ext = entry.path().extension().string();
                    if (ext.empty()) {
                        ext = "[no extension]";
                    }
                    stats.extensionCounts[ext]++;
                    stats.totalFiles++;
                }
            }
        } catch (const fs::filesystem_error&) {
            // Access denied
        }

        return stats;
    }
};

}

#endif
