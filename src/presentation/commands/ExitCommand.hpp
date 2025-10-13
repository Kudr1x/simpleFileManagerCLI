#ifndef EXITCOMMAND_HPP
#define EXITCOMMAND_HPP

#include "../ICommand.hpp"
#include <iostream>

namespace presentation {

    class ExitCommand : public ICommand {
    private:
        bool& shouldExit;

    public:
        explicit ExitCommand(bool& exitFlag) : shouldExit(exitFlag) {}

        void execute() override {
            shouldExit = true;
        }

        [[nodiscard]] std::string getName() const override {
            return "exit";
        }
    };

}

#endif
