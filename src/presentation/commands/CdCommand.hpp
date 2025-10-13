#ifndef CDCOMMAND_HPP
#define CDCOMMAND_HPP

#include "../ICommand.hpp"
#include "../../application/IFileSystemService.hpp"
#include <iostream>
#include <memory>

namespace presentation {

    class CdCommand : public ICommand {
    private:
        std::shared_ptr<application::IFileSystemService> service;
        std::string targetPath;

    public:
        CdCommand(std::shared_ptr<application::IFileSystemService> svc,
                  const std::string& path)
            : service(svc), targetPath(path) {}

        void execute() override {
            if (!service->changeDirectory(targetPath)) {
                std::cerr << "Not a directory" << std::endl;
            }
        }

        [[nodiscard]] std::string getName() const override {
            return "cd";
        }
    };

}

#endif
