#pragma once
#include "script_line.h"
#include <string>
#include <vector>

class Memory;
class SyntaxValidator;
class ScriptLine;
class ErrorReporter;
class Tokenizer;
class CommentRemover;
class HighlightManager;
class Location;

class Compiler {
private:
    Memory *memory;
    CommentRemover *comment_remover;
    SyntaxValidator *syntax_validator;
    ErrorReporter *error_reporter;
    Tokenizer *tokenizer;
    HighlightManager *highlight_manager;
    std::vector<ScriptLine> script_lines;
public:
    Compiler();
    std::string compile_and_run(std::string path);
    void compile_file(std::string path);
    void compile_line(ScriptLine *line);
    std::string run_file();
    std::string run_line(std::vector<class Token *> tokens);
};