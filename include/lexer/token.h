#pragma once
#include <string>
#include <vector>
#include "location.h"

enum TokenType {
    IDENTIFIER,
    NUMBER_LITERAL,
    STRING_LITERAL,
    BOOLEAN_LITERAL,
    OPERATOR,
    UNKNOWN
};

class Token {
private:
    TokenType type;
    std::string value;
    Location location;

    void infer_type();
    bool is_identifier() const;
    bool is_number_literal() const;
    bool is_integer() const;
    bool is_float() const;
    bool is_string_literal() const;
    bool is_boolean_literal() const;
    bool is_operator() const;
    
public:
    Token(const char& value);
    Token(const std::string& value);
    Token(const std::string& value, const Location& location);
    Token(const char value, const Location& location);

    TokenType get_type() const;
    const std::string& get_value() const;
    const Location& get_location() const;
    
    bool is_empty() const;
};