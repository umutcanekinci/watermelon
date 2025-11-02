#include <string>
#include "operator.h"

using namespace std;

Operator::Operator(char value) : value(value) {}

char Operator::get_value() const {
    return value;
}

bool Operator::is_parenthesis() const {
    return value == '(' || value == ')';
}

bool Operator::is_multiplication_or_division() const {
    return value == '/' || value == '*';
}

bool Operator::is_addition_or_substraction() const {
    return value == '+' || value == '-';
}

bool Operator::is_operator() const {
    return  is_addition_or_substraction() ||
            is_multiplication_or_division() ||
            is_parenthesis();
}

int Operator::get_priority() const {
    if (is_parenthesis())
        return 1;
    else if (is_multiplication_or_division())
            return 2;
        else if (is_addition_or_substraction())
            return 3;
        return -1;
}

bool Operator::operator==(char c) const {
    return c == get_value();
}

bool Operator::operator!=(char c) const {
    return c != get_value();
}


ostream & operator<<(ostream & Str, Operator* const & v) { 
    Str << std::string(1, v->get_value()) + " [" + std::to_string(v->get_priority()) + "]";
    return Str;
}