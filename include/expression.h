#pragma once
#include <vector>
#include <string>
#include "stack.h"

class Token;
class Operator;

class Expression {
private:
    std::vector<Token *> tokens;
public:
    Expression(std::vector<Token *> tokens);
    void substitute_variables(const std::vector<std::pair<std::string, int>>& variables);
    int evaluate();
    std::vector<Token *> to_postfix();
    bool check_parenthesis(std::string &infix);
    void add_operator_to_stack(std::vector<Token *> *postfix, Stack<Operator> *operator_stack, Operator *current);
    void infix_to_postfix_char(Token * current, std::vector<Token *> &postfix, int i, Stack<Operator> *operator_stack);
    std::string to_string() const;
};