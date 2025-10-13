#ifndef VISUALCOMMAND_HPP
#define VISUALCOMMAND_HPP

#include "../ICommand.hpp"
#include "../../application/IFileSystemService.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace presentation {

class VisualCommand : public ICommand {
private:
    std::shared_ptr<application::IFileSystemService> service;
    
    std::string createBar(size_t count, size_t maxCount, size_t barWidth = 40) {
        if (maxCount == 0) return "";
        
        size_t filledWidth = (count * barWidth) / maxCount;
        std::string bar;
        
        for (size_t i = 0; i < filledWidth; ++i) {
            bar += "█";
        }
        
        return bar;
    }

public:
    explicit VisualCommand(std::shared_ptr<application::IFileSystemService> svc) 
        : service(svc) {}

    void execute() override {
        auto stats = service->getFileTypeStats();
        
        if (stats.totalFiles == 0) {
            std::cout << "No files in current directory" << std::endl;
            return;
        }
        
        std::cout << "File types distribution:" << std::endl;
        std::cout << std::endl;
        
        std::vector<std::pair<std::string, size_t>> sortedStats(
            stats.extensionCounts.begin(), 
            stats.extensionCounts.end()
        );
        
        std::sort(sortedStats.begin(), sortedStats.end(), 
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
        
        size_t maxCount = sortedStats.empty() ? 0 : sortedStats[0].second;
        
        for (const auto& [ext, count] : sortedStats) {
            double percentage = (static_cast<double>(count) / stats.totalFiles) * 100.0;
            
            std::cout << std::left << std::setw(15) << ext << " ";
            std::cout << createBar(count, maxCount) << " ";
            std::cout << std::right << std::setw(5) << std::fixed << std::setprecision(1) 
                      << percentage << "% ";
            std::cout << "(" << count << " files)" << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "Total: " << stats.totalFiles << " files" << std::endl;
    }

    std::string getName() const override {
        return "visual";
    }
};

}

#endif
