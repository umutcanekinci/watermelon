#pragma once
#include <vector>
#include <string>
#include "stack.h"

class Value;
class Token;
class Memory;

// Expression is a list of tokens which can be evaluated to a value.
class Expression {
private:
    std::vector<Token *> tokens;
public:
    Expression(std::vector<Token *> tokens);
    Expression *substitute_variables(Memory *memory);
    Expression *to_postfix();
    Value evaluate(Memory *memory);
    void add_operator_to_stack(Token *current, Stack<Token *> *postfix, Stack<Token *> *operator_stack);
    void infix_to_postfix_char(Token * current, Stack<Token *> &postfix, int i, Stack<Token *> *operator_stack);
    std::string to_string() const;

    bool are_parentheses_balanced(std::string &infix);
};