#pragma once

#include <filesystem>
#include <string>
#include <set>
#include <vector>

namespace fs = std::filesystem;

struct Command {
    std::string flag;
    std::vector<std::string> params;
};

using CommandPointer = std::shared_ptr<Command>;

struct ParseResults {
    std::string input_file;
    std::string output_file;
    std::vector<CommandPointer> commands;
};

// std::set<std::string> filter_flags = {"-crop", "-gs", "-neg", "-sharp", "-edge", "-blur"};

ParseResults Parse(int argc, char** argv);