#include "location.h"
#include "token.h"
#include "operator_table.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

Token::Token(const char& value) {
    this->value = string(1, value);
}

Token::Token(const string& value) {
    this->value = value;
}

Token::Token(const string& value, const Location& location) {
    this->value = value;
    this->location = location;
}

Token::Token(const char value, const Location& location) {
    this->value = string(1, value);
    this->location = location;
}

const string& Token::get_value() const {
    return value;
}

const Location& Token::get_location() const {
    return location;
}

bool Token::is_empty() const {
    return value.empty();
}

bool Token::is_variable() const {
return !is_number() && !is_operator() && !is_bool() && !is_string();
}

bool Token::is_bool() const {
    return value == "true" || value == "false";
}

bool Token::is_string() const {
    return value.length() >= 2 && value.front() == '"' && value.back() == '"';
}

bool Token::is_number() const {
    return is_float() || is_integer();
}

bool Token::is_float() const {
    if (std::count(value.begin(), value.end(), '.') != 1)
        return false;

    for (char const &ch : value) {
        if (std::isdigit(ch) == 0 && ch != '.') return false;
    }
    return true;
}

bool Token::is_integer() const {
    for (char const &ch : value) {
        if (!std::isdigit(ch)) return false;
    }
    return true;
}

bool Token::is_operator() const {
    if (value.length() != 1)
        return false;
        
    return OperatorTable::TABLE.find(value) != OperatorTable::TABLE.end();
}