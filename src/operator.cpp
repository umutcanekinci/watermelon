#ifndef OPERATOR_CPP
#define OPERATOR_CPP

#include <string>
#include <iostream>
using namespace std;

class Operator {
    char value;
public:
    Operator(char value) : value(value) {}

    char get_value() const {
        return value;
    }

    bool is_parenthesis() const {
        return value == '(' || value == ')';
    }

    bool is_multiplication_or_division() const {
        return value == '/' || value == '*';
    }

    bool is_addition_or_substraction() const {
        return value == '+' || value == '-';
    }

    bool is_operator() const {
        return  is_addition_or_substraction() ||
                is_multiplication_or_division() ||
                is_parenthesis();
    }

    int get_priority() const {
        if (is_parenthesis())
            return 1;
        else if (is_multiplication_or_division())
            return 2;
        else if (is_addition_or_substraction())
            return 3;
        return -1;
    }

    bool operator==(char c) {
        return c == get_value();
    }

    bool operator!=(char c) {
        return c != get_value();
    }
};

ostream & operator<<(ostream & Str, Operator* const & v) { 
    Str << std::string(1, v->get_value()) + " [" + std::to_string(v->get_priority()) + "]";
    return Str;
}

#endif