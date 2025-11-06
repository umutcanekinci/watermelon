#include "script_line.h"
#include "token.h"
#include "expression.h"
#include <stdexcept>
#include <string>
#include <value.h>
using namespace std;

ScriptLine::ScriptLine(int number, const string& line) {
    this->number = number;
    this->line = line;
}

bool ScriptLine::is_comment() const {
    return line.rfind("//", 0) == 0; 
}

bool ScriptLine::is_empty() const {
    return line.empty();
}

string ScriptLine::to_string() const {
    return "line " + std::to_string(number) + ": " + line;
}