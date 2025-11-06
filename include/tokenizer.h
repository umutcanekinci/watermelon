#pragma once

#include <string>
#include <vector>

class Token;

class Tokenizer {
public:
    static std::vector<Token *> tokenize(const std::string& line);
};
