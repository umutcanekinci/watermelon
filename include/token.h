#pragma once
#include <string>
#include <vector>

class Token {
private:
    std::string value;
public:
    Token(const std::string& value);
    const std::string& get_value() const;
    void set_value(const std::string& new_value);
    int get_precedence() const;

    bool is_empty() const;
    bool is_variable() const;
    bool is_number() const;
    bool is_operator() const;
    bool is_valid_variable() const;
};

// ostream & operator<<(ostream & Str, Operator* const & v) { 
//     Str << v->get_value() + " [" + std::to_string(v->get_precedence()) + "]";
//     return Str;
// }