#pragma once
#include <string>
#include <vector>

class ScriptLine;

class Compiler {
    std::vector<std::pair<std::string, int>> variables;
public:
    std::string compile_line(ScriptLine *line);
    std::string compile_file(std::string path);
};