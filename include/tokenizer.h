#pragma once
#include "script_line.h"
#include <string>
#include <vector>

class Token;

class Tokenizer {
public:
    static std::vector<Token *> tokenize(const ScriptLine& line);
};
