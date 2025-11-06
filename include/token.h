#pragma once
#include <string>
#include <vector>

class Token {
private:
    std::string value;
public:
    Token(const std::string& value);
    Token(const char value) : Token(std::string(1, value)) {}
    const std::string& get_value() const;

    bool is_empty() const;
    bool is_variable() const;
    bool is_bool() const;
    bool is_string() const;
    bool is_number() const;
    bool is_float() const;
    bool is_integer() const;
    bool is_operator() const;
};