#include <stdexcept>

#include "parser.h"
#include <iostream>

void CheckArgCount(int argc, char** argv) {
    if (argc < 3) {
        throw std::invalid_argument("Not enough arguments");
    }
}

void CheckFirstFlag(int argc, char** argv) {
    if (*argv[3] != '-') {
        throw std::invalid_argument("Filter's name must start with a dash.");
    }
}

ParseResults ParseAfterChecks(int argc, char** argv) {
    std::string input_file = argv[1];
    std::string output_file = argv[2];

    CheckFirstFlag(argc, argv);

    std::vector<CommandPointer> commands;

    std::string flag;
    std::vector<std::string> params;
    int i = 3;
    while (i < argc) {
        flag = argv[i];
        ++i;
        while (i < argc && *argv[i] != '-') {
            params.push_back(argv[i]);
            ++i;
        }
        commands.emplace_back(std::make_shared<Command>(flag, params));
        params.clear();
    }
    return ParseResults(input_file, output_file, commands);
}

ParseResults Parse(int argc, char** argv) {
    CheckArgCount(argc, argv);

    std::vector<CommandPointer> commands;
    if (argc == 3) {
        return ParseResults(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]), commands);
    }
    return ParseAfterChecks(argc, argv);
}