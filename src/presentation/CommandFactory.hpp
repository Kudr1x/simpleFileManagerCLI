#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "ICommand.hpp"
#include "commands/PwdCommand.hpp"
#include "commands/LsCommand.hpp"
#include "commands/CdCommand.hpp"
#include "commands/StatCommand.hpp"
#include "commands/ExitCommand.hpp"
#include "commands/VisualCommand.hpp"
#include "../application/IFileSystemService.hpp"
#include <memory>
#include <string>
#include <sstream>
#include <vector>

namespace presentation {

enum class CommandType {
    PWD,
    LS,
    CD,
    STAT,
    VISUAL,
    EXIT,
    UNKNOWN
};

class CommandFactory {
private:
    std::shared_ptr<application::IFileSystemService> service;
    bool& exitFlag;

    CommandType parseCommandType(const std::string& input) {
        if (input == "pwd") return CommandType::PWD;
        if (input == "ls") return CommandType::LS;
        if (input.substr(0, 2) == "cd") return CommandType::CD;
        if (input == "stat") return CommandType::STAT;
        if (input == "visual") return CommandType::VISUAL;
        if (input == "exit") return CommandType::EXIT;
        return CommandType::UNKNOWN;
    }

    std::vector<std::string> parseInput(const std::string& input) {
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        return tokens;
    }

public:
    CommandFactory(std::shared_ptr<application::IFileSystemService> svc, 
                   bool& exit) 
        : service(svc), exitFlag(exit) {}

    std::unique_ptr<ICommand> createCommand(const std::string& input) {
        auto tokens = parseInput(input);
        
        if (tokens.empty()) {
            return nullptr;
        }
        
        CommandType cmdType = parseCommandType(input);
        
        switch (cmdType) {
        case CommandType::PWD:
            return std::make_unique<PwdCommand>(service);
        case CommandType::LS:
            return std::make_unique<LsCommand>(service);
        case CommandType::CD:
            if (tokens.size() < 2) {
                std::cerr << "Argument required" << std::endl;
                return nullptr;
            }
            return std::make_unique<CdCommand>(service, tokens[1]);
        case CommandType::STAT:
            return std::make_unique<StatCommand>(service);
        case CommandType::VISUAL:
            return std::make_unique<VisualCommand>(service);
        case CommandType::EXIT:
            return std::make_unique<ExitCommand>(exitFlag);
        case CommandType::UNKNOWN:
            std::cerr << "Unknown command" << std::endl;
            return nullptr;
        }
        
        return nullptr;
    }
};

}

#endif
