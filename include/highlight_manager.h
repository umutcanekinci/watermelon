#pragma once
#include <string>
#include <vector>

class Token;

class HighlightManager {
public:
    std::string highlight_token(std::vector<Token *> tokens, const Token *token);
    std::string highlight_string(std::string &line, size_t start_pos, size_t length);
};