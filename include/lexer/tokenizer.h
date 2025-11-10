#pragma once
#include "script_line.h"
#include <string>
#include <vector>

class Token;

class Tokenizer {
public:
    std::vector<Token *> tokenize(const ScriptLine& line);
};
