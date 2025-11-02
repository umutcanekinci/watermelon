#pragma once

class Operator {
    char value;
public:
    Operator(char value);
    char get_value() const;
    bool is_parenthesis() const;
    bool is_multiplication_or_division() const;
    bool is_addition_or_substraction() const;
    bool is_operator() const;
    int get_priority() const;
    bool operator==(char c) const;
    bool operator!=(char c) const;
};