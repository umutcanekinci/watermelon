#include "token.h"
#include <stdexcept>
using namespace std;

Token::Token(const string& value) {
    set_value(value);
}

Token::Type Token::get_type() const {
    return type;
}

const string& Token::get_value() const {
    return value;
}

void Token::set_value(const string& new_value) {
    value = new_value;
    type = determine_type(new_value);
}

bool Token::is_number(const string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

bool Token::is_operator(const string& s) {
    if (s.length() != 1) return false;
    char ch = s[0];
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
}

bool Token::is_operator() const {
    return is_operator(value);
}

bool Token::is_number() const {
    return is_number(value);
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

Token::Type Token::determine_type(const string& token) {
    if (token.empty()) {
        throw std::runtime_error("Empty token cannot be classified.");
    }

    // Check if the token is a number
    if (is_number(token)) {
        return NUMBER;
    }

    // Check if the token is an operator
    if (token.length() == 1) {
        char ch = token[0];
        if (is_operator(string(1, ch))) {
            return OPERATOR;
        }
    }

    // Check if the token is a parenthesis
    if (token == "(" || token == ")") {
        return PARENTHESIS;
    }

    return VARIABLE;
}