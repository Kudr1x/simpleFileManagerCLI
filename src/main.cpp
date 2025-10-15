#include "application/FileSystemService.hpp"
#include "presentation/CommandFactory.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>

std::string getShortPath(const std::string& fullPath) {
    const char* home = std::getenv("HOME");
    std::string homeDir = home ? home : "";

    if (!homeDir.empty() && fullPath.find(homeDir) == 0) {
        return "~" + fullPath.substr(homeDir.length());
    }

    return fullPath;
}

int main() {
    auto fileSystemService = std::make_shared<application::FileSystemService>();
    bool shouldExit = false;

    presentation::CommandFactory commandFactory(fileSystemService, shouldExit);

    std::cout << "Simple file manager" << std::endl;
    std::cout << "Commands: pwd, ls, cd, stat, visual, exit" << std::endl;
    std::cout << std::endl;

    while (!shouldExit) {
        std::string currentPath = fileSystemService->getCurrentPath();
        std::string shortPath = getShortPath(currentPath);

        std::cout << shortPath << "> ";

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
