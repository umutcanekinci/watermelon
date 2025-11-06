#pragma once
#include <string>
#include <vector>
#include "value.h"

class Memory;
class Token;
class Expression;

class ScriptLine {
private:
    int number;
    std::string line;
    std::vector<Token *> tokens;
public:
    ScriptLine(int number, const std::string& line);
    bool is_comment() const;
    bool is_empty() const;
    void compile(Memory *memory);
    std::string to_string() const;
};
