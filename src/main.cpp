#include "application/FileSystemService.hpp"
#include "presentation/CommandFactory.hpp"
#include <iostream>
#include <string>
#include <memory>

int main() {
    auto fileSystemService = std::make_shared<application::FileSystemService>();
    bool shouldExit = false;

    presentation::CommandFactory commandFactory(fileSystemService, shouldExit);

    std::cout << "Simple file manager" << std::endl;
    std::cout << "Commands: pwd, ls, cd, stat, visual, exit" << std::endl;
    std::cout << std::endl;

    while (!shouldExit) {
        std::cout << "fm> ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        auto command = commandFactory.createCommand(input);
        if (command) {
            command->execute();
        }
    }

    return 0;
}
