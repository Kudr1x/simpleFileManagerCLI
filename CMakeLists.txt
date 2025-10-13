cmake_minimum_required(VERSION 4.0)
project(simpleFileManagerCLI)

set(CMAKE_CXX_STANDARD 17)

add_executable(simpleFileManagerCLI src/main.cpp
        src/domain/FileSystemEntity.hpp
        src/domain/DirectoryStats.hpp
        src/application/IFileSystemService.hpp
        src/application/FileSystemService.hpp
        src/presentation/ICommand.hpp
        src/presentation/commands/PwdCommand.hpp
        src/presentation/commands/LsCommand.hpp
        src/presentation/commands/CdCommand.hpp
        src/presentation/commands/StatCommand.hpp
        src/presentation/commands/ExitCommand.hpp
        src/presentation/CommandFactory.hpp
        src/presentation/commands/VisualCommand.hpp)
