#pragma once
#include <string>
#include <vector>
#include "location.h"

class Token {
private:
    std::string value;
    Location location;
public:
    Token(const std::string& value, const Location& location);
    Token(const char value, const Location& location);

    const std::string& get_value() const;
    const Location& get_location() const;
    
    bool is_empty() const;
    bool is_variable() const;
    bool is_bool() const;
    bool is_string() const;
    bool is_number() const;
    bool is_float() const;
    bool is_integer() const;
    bool is_operator() const;
};