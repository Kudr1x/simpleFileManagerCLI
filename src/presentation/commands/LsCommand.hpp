#ifndef LSCOMMAND_HPP
#define LSCOMMAND_HPP

#include "../ICommand.hpp"
#include "../../application/IFileSystemService.hpp"
#include <iostream>
#include <memory>

namespace presentation {

    class LsCommand : public ICommand {
    private:
        std::shared_ptr<application::IFileSystemService> service;

    public:
        explicit LsCommand(std::shared_ptr<application::IFileSystemService> svc)
            : service(svc) {}

        void execute() override {
            auto entities = service->listDirectory();

            for (const auto& entity : entities) {
                std::cout << entity.name;
                if (entity.type == domain::EntityType::Directory) {
                    std::cout << "/";
                }
                std::cout << std::endl;
            }
        }

        [[nodiscard]] std::string getName() const override {
            return "ls";
        }
    };

}

#endif
