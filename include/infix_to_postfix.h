#pragma once
#include <iostream>
#include "operator.h"
#include "stack.h"

bool check_parenthesis(string &infix);

void add_operator_to_stack(string *postfix, Stack<Operator> *operator_stack, Operator *current);

void infix_to_postfix_char(string &infix, string &postfix, int i, Stack<Operator> *operator_stack);

string InfixToPostfix(string infix);