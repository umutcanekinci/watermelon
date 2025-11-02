#include "token.h"
using namespace std;

Token::Token(Type type, const string& value) : type(type), value(value) {}

Token::Type Token::get_type() const {
    return type;
}

string Token::get_value() const {
    return value;
}

bool Token::empty() const {
    return value.empty();
}

bool is_number(const string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

bool is_operator(const string& s) {
    if (s.length() != 1) return false;
    char ch = s[0];
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
}

Token::Type Token::determine_type(const string& token) {
    if (token.empty()) {
        throw "Empty token cannot be classified.";
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