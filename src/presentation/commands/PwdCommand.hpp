#ifndef PWDCOMMAND_HPP
#define PWDCOMMAND_HPP

#include "../ICommand.hpp"
#include "../../application/IFileSystemService.hpp"
#include <iostream>
#include <memory>

namespace presentation {

    class PwdCommand : public ICommand {
    private:
        std::shared_ptr<application::IFileSystemService> service;

    public:
        explicit PwdCommand(std::shared_ptr<application::IFileSystemService> svc)
            : service(svc) {}

        void execute() override {
            std::cout << service->getCurrentPath() << std::endl;
        }

        [[nodiscard]] std::string getName() const override {
            return "pwd";
        }
    };

}

#endif
