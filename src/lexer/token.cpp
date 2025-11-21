#include "location.h"
#include "token.h"
#include "operator_table.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

Token::Token(const char& value) {
    this->value = string(1, value);
    infer_type();
}

Token::Token(const string& value) {
    this->value = value;
    infer_type();
}

Token::Token(const string& value, const Location& location) {
    this->value = value;
    this->location = location;
    infer_type();
}

Token::Token(const char value, const Location& location) {
    this->value = string(1, value);
    this->location = location;
    infer_type();
}

TokenType Token::get_type() const {
    return type;
}

const string& Token::get_value() const {
    return value;
}

const Location& Token::get_location() const {
    return location;
}

void Token::infer_type() {
    if (is_identifier())          type = IDENTIFIER;     
    else if (is_number_literal()) type = NUMBER_LITERAL;
    else if (is_string_literal()) type = STRING_LITERAL;
    else if (is_boolean_literal())type = BOOLEAN_LITERAL;
    else if (is_operator())       type = OPERATOR;
    else                          type = UNKNOWN;
}

bool Token::is_empty() const {
    return value.empty();
}

bool Token::is_identifier() const {
    if (value.empty())
        return false;

    if (!(isalpha(value[0]) || value[0] == '_'))
        return false;

    for (char const &ch : value) {
        if (!(isalnum(ch) || ch == '_'))
            return false;
    }
    return true;
}

bool Token::is_boolean_literal() const {
    return value == "true" || value == "false";
}

bool Token::is_string_literal() const {
    return value.length() >= 2 && value.front() == '"' && value.back() == '"';
}

bool Token::is_number_literal() const {
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