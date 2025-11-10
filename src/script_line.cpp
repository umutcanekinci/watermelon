#include "script_line.h"
#include "token.h"
#include "expression.h"
#include <stdexcept>
#include <string>
#include <value.h>
using namespace std;

ScriptLine::ScriptLine(const Location& location, const string& line) {
    this->location = location;
    this->line = line;
}

string ScriptLine::get_text() const {
    return line;
}

Location ScriptLine::get_location() const {
    return location;
}

bool ScriptLine::is_comment() const {
    return line.rfind("//", 0) == 0; 
}

bool ScriptLine::is_empty() const {
    return line.empty();
}

string ScriptLine::to_string() const {
    return location.to_string() + " " + line;
}