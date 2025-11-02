#pragma once
#include <string>
#include "stack.h"
using namespace std;

class Operator;

bool check_parenthesis(string &infix);

void add_operator_to_stack(string *postfix, Stack<Operator> *operator_stack, Operator *current);

void infix_to_postfix_char(string &infix, string &postfix, int i, Stack<Operator> *operator_stack);

string infix_to_postfix(string infix);