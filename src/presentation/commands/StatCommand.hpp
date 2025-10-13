#ifndef STATCOMMAND_HPP
#define STATCOMMAND_HPP

#include "../ICommand.hpp"
#include "../../application/IFileSystemService.hpp"
#include <iostream>
#include <memory>

namespace presentation {

    class StatCommand : public ICommand {
    private:
        std::shared_ptr<application::IFileSystemService> service;

    public:
        explicit StatCommand(std::shared_ptr<application::IFileSystemService> svc)
            : service(svc) {}

        void execute() override {
            auto stats = service->getDirectoryStats();

            std::cout << "Total: " << stats.totalCount << std::endl;
            std::cout << "Files: " << stats.fileCount << std::endl;
            std::cout << "Dirs: " << stats.directoryCount << std::endl;
        }

        [[nodiscard]] std::string getName() const override {
            return "stat";
        }
    };

}

#endif
