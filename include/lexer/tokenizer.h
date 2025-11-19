#pragma once
#include "script_line.h"
#include <string>
#include <vector>

class Token;

class Tokenizer {
public:
    std::vector<Token *> tokenize(const ScriptLine& line);
    void flush_buffer(std::vector<Token*>& tokens, std::string& buffer, Location& line_location, int end_col);
    Token *create_token(const std::string &value, Location &line_location, int end_column);
};
