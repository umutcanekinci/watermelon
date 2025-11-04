#include "token.h"
#include <stdexcept>
using namespace std;

Token::Token(const string& value) {
    set_value(value);
}

const string& Token::get_value() const {
    return value;
}

void Token::set_value(const string& new_value) {
    value = new_value;
}

int Token::get_precedence() const {
    if (value == "(" || value == ")")
        return 1;
    else if (value == "*" || value == "/")
        return 2;
    else if (value == "+" || value == "-")
        return 3;
    return -1;
}

bool Token::is_valid_variable() const {
    if (value.empty() || std::isdigit(value[0])) {
        return false;
    }

    // Check that all characters are alphanumeric or underscore
    for (char const &ch : value) {
        if (!std::isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

bool Token::is_empty() const {
    return value.empty();
}

bool Token::is_variable() const {
    return !is_number() && !is_operator();
}

bool Token::is_number() const {
    for (char const &ch : value) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

bool Token::is_operator() const {
    if (value.length() != 1)
        return false;
    char ch = value[0];
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')';
}