#pragma once
#include <vector>
#include <string>
#include "stack.h"

class Token;
class Operator;
class Memory;

// Expression is a list of tokens which can be evaluated to a value.
class Expression {
private:
    std::vector<Token *> tokens;
public:
    Expression(std::vector<Token *> tokens);
    Expression *substitute_variables(Memory *memory);
    int evaluate();
    Expression *to_postfix();
    bool check_parenthesis(std::string &infix);
    void add_operator_to_stack(Operator *current, std::vector<Token *> *postfix, Stack<Operator *> *operator_stack);
    void infix_to_postfix_char(Token * current, std::vector<Token *> &postfix, int i, Stack<Operator *> *operator_stack);
    std::string to_string() const;
};