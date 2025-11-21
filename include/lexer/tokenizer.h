#pragma once
#include "script_line.h"
#include <string>
#include <vector>

class Token;
class ErrorReporter;

class Tokenizer {
private:
    ErrorReporter* error_reporter;
public:
    Tokenizer(ErrorReporter& reporter);
    std::vector<Token *> tokenize(const ScriptLine& line);
    void flush_buffer(const std::string &line, std::vector<Token*>& tokens, std::string& buffer, Location& line_location, int end_col);
    Token *create_token(const std::string &line, const std::string &value, Location &line_location, int end_column);

    void report_lex_error(const std::string &message, const Location &loc, const std::string &line_text);
};
