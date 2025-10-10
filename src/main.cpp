#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void show_pwd(const fs::path& current_path) {
    std::cout << current_path.string() << std::endl;
}

void list_dir(const fs::path& path) {
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

bool change_dir(fs::path& current_path, const std::string& cmd_path) {
    fs::path target;
    if (fs::path(cmd_path).is_absolute()) {
        target = fs::path(cmd_path);
    } else {
        target = current_path / cmd_path;
    }
    try {
        target = fs::canonical(target);
        if (fs::exists(target) && fs::is_directory(target)) {
            current_path = target;
            return true;
        } else {
            std::cerr << "Not a directory" << std::endl;
        }
    } catch (...) {
        std::cerr << "Not a directory" << std::endl;
    }
    return false;
}

void dir_stats(const fs::path& path) {
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

int main() {
    fs::path current_path = fs::current_path();
    std::string cmd;
    std::cout << "Simple file manager" << std::endl;
    std::cout << "Commands: pwd, ls, cd <name>, stat, exit" << std::endl;

    while (true) {
        std::cout << "fm> ";
        std::getline(std::cin, cmd);
        if (cmd == "pwd") {
            show_pwd(current_path);
        } else if (cmd == "ls") {
            list_dir(current_path);
        } else if (cmd.substr(0, 2) == "cd") {
            auto pos = cmd.find(' ');
            if (pos != std::string::npos) {
                std::string arg = cmd.substr(pos + 1);
                change_dir(current_path, arg);
            } else {
                std::cerr << "Argument required" << std::endl;
            }
        } else if (cmd == "stat") {
            dir_stats(current_path);
        } else if (cmd == "exit") {
            break;
        } else if (cmd.empty()) {
            continue;
        } else {
            std::cerr << "Unknown command" << std::endl;
        }
    }
    return 0;
}
