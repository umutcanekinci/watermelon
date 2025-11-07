#pragma once
#include <string>
#include <vector>
#include "value.h"
#include "location.h"

class Memory;
class Token;
class Expression;
class ScriptLine {
private:
    std::string line;
    Location location;
public:
    ScriptLine(const Location& location, const std::string& line);

    std::string get_text() const;
    Location get_location() const;

    bool is_comment() const;
    bool is_empty() const;
    std::string to_string() const;
};
