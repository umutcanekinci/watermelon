#pragma once
#include <string>
#include <vector>

class Token {
public:
    enum Type {
        NUMBER,
        OPERATOR,
        VARIABLE,
        PARENTHESIS
    };

    Token(const std::string& value);
    Type get_type() const;
    const std::string& get_value() const;
    void set_value(const std::string& new_value);
    static bool is_number(const std::string& s);
    bool is_number() const;
    bool is_operator() const;
    static bool is_operator(const std::string& s);
    static Type determine_type(const std::string& token);
    bool is_empty() const;
    bool is_valid_variable() const;
    bool is_variable() const;
private:
    Type type;
    std::string value;
};