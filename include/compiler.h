#pragma once
#include <string>
#include <vector>

class Memory;
class SyntaxValidator;
class ScriptLine;
class ErrorReporter;

class Compiler {
private:
    Memory *memory;
    SyntaxValidator *syntax_validator;
    ErrorReporter *error_reporter;
public:
    Compiler();
    std::string run();
    void compile_file(std::string path);
    void compile_line(std::vector<class Token *> tokens);
};