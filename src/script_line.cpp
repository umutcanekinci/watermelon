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

Location ScriptLine::get_location() const {
    return location;
}

string ScriptLine::get_text() const {
    return line;
}

bool ScriptLine::is_empty() const {
    return line.empty();
}

string ScriptLine::to_string() const {
    return location.to_string() + " " + line;
}