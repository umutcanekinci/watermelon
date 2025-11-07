#pragma once
#include <string>
#include <vector>

class Memory;
class SyntaxValidator;
class ScriptLine;

class Compiler {
private:
    Memory *memory;
    SyntaxValidator *syntax_validator;
public:
    Compiler();
    std::string compile_file(std::string path);
    std::string compile_line(std::vector<class Token *> tokens);
};