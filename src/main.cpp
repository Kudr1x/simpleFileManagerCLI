#include <iostream>
#include <filesystem>
#include <string>
#include <memory>

namespace fs = std::filesystem;

enum class CommandType {
    PWD,
    LS,
    CD,
    STAT,
    EXIT,
    UNKNOWN
};

CommandType parse_command(const std::string& input) {
    if (input == "pwd") return CommandType::PWD;
    if (input == "ls") return CommandType::LS;
    if (input.substr(0, 2) == "cd") return CommandType::CD;
    if (input == "stat") return CommandType::STAT;
    if (input == "exit") return CommandType::EXIT;
    return CommandType::UNKNOWN;
}

std::string get_cd_arg(const std::string& input) {
    auto pos = input.find(' ');
    if (pos != std::string::npos)
        return input.substr(pos + 1);
    return "";
}

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

class PwdCommand : public ICommand {
    fs::path& current_path;
public:
    explicit PwdCommand(fs::path& path) : current_path(path) {}
    void execute() override {
        std::cout << current_path.string() << std::endl;
    }
};

class LsCommand : public ICommand {
    fs::path& path;
public:
    explicit LsCommand(fs::path& p) : path(p) {}
    void execute() override {
        try {
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << entry.path().filename().string();
                if (fs::is_directory(entry.status())) std::cout << "/";
                std::cout << std::endl;
            }
        } catch (...) {
            std::cerr << "Access denied" << std::endl;
        }
    }
};

class CdCommand : public ICommand {
    fs::path& current_path;
    std::string target_path;
public:
    CdCommand(fs::path& cur, const std::string& path) : current_path(cur), target_path(path) {}
    void execute() override {
        fs::path target = fs::path(target_path).is_absolute() ? fs::path(target_path) : current_path / target_path;
        try {
            target = fs::canonical(target);
            if (fs::exists(target) && fs::is_directory(target))
                current_path = target;
            else
                std::cerr << "Not a directory" << std::endl;
        } catch (...) {
            std::cerr << "Not a directory" << std::endl;
        }
    }
};

class StatCommand : public ICommand {
    fs::path& path;
public:
    explicit StatCommand(fs::path& p) : path(p) {}
    void execute() override {
        size_t files = 0, dirs = 0, total = 0;
        try {
            for (const auto& entry : fs::directory_iterator(path)) {
                total++;
                if (fs::is_directory(entry.status())) dirs++;
                else if (fs::is_regular_file(entry.status())) files++;
            }
            std::cout << "Total: " << total << std::endl;
            std::cout << "Files: " << files << std::endl;
            std::cout << "Dirs: " << dirs << std::endl;
        } catch (...) {
            std::cerr << "Access denied" << std::endl;
        }
    }
};

class ExitCommand : public ICommand {
    bool& should_exit;
public:
    explicit ExitCommand(bool& flag) : should_exit(flag) {}
    void execute() override { should_exit = true; }
};

std::unique_ptr<ICommand> CommandFactory(const std::string& input, fs::path& current_path, bool& should_exit) {
    CommandType cmd_type = parse_command(input);
    switch (cmd_type) {
    case CommandType::PWD:
        return std::make_unique<PwdCommand>(current_path);
    case CommandType::LS:
        return std::make_unique<LsCommand>(current_path);
    case CommandType::CD: {
        std::string arg = get_cd_arg(input);
        if (arg.empty()) {
            std::cerr << "Argument required" << std::endl;
            return nullptr;
        }
        return std::make_unique<CdCommand>(current_path, arg);
    }
    case CommandType::STAT:
        return std::make_unique<StatCommand>(current_path);
    case CommandType::EXIT:
        return std::make_unique<ExitCommand>(should_exit);
    case CommandType::UNKNOWN:
        if (!input.empty())
            std::cerr << "Unknown command" << std::endl;
        return nullptr;
    }
    return nullptr;
}

int main() {
    fs::path current_path = fs::current_path();
    bool should_exit = false;
    std::string input;

    std::cout << "Simple file manager\nAllowed commands: pwd, ls, cd <name>, stat, exit\n";

    while (!should_exit) {
        std::cout << "fm> ";
        std::getline(std::cin, input);

        auto command = CommandFactory(input, current_path, should_exit);
        if (command) {
            command->execute();
        }
    }
    return 0;
}
