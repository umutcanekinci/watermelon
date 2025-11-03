#pragma once
#include <string>
#include <vector>

class Memory;
class ScriptLine;

class Compiler {
private:
    Memory *memory;
public:
    Compiler();
    std::string compile_line(ScriptLine *line);
    std::string compile_file(std::string path);
};