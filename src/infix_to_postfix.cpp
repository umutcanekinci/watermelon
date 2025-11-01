#ifndef INFIX_TO_POSTFIX_CPP
#define INFIX_TO_POSTFIX_CPP

#include <iostream>
#include "operator.cpp"
#include "stack.cpp"

void add_operator_to_stack(string *postfix, Stack<Operator> *operator_stack, Operator *current) {
    // if (current->is_parenthesis()) {
    //     operator_stack->push(current);
    //     return;
    // }

    // If stack is empty or current operator is (, just push it.
    if (operator_stack->is_empty() || *current == '(') {
        // cout << "BIGGG";
        operator_stack->push(current);
        return;
    }

    // If operator is closing parenthesis, all operators should popped to the string.
    Operator* top = operator_stack->get();
    
    if (*current == ')') {
        if (*top == '(') {
            operator_stack->pop();
            return;
        }
        operator_stack->pop_to_string(postfix);
        add_operator_to_stack(postfix, operator_stack, current);
        return;
    }

    // If current <= top, pop the top to the string and use recursion to check new top(s).
    if (current->get_priority() >= top->get_priority()) {
        if (*top == '(') {
            operator_stack->push(current);
            return;
        }

        operator_stack->pop_to_string(postfix);
        add_operator_to_stack(postfix, operator_stack, current);
        return;
    }

    operator_stack->push(current);
}

void InfixToPostfixChar(string &infix, string &postfix, int i, Stack<Operator> *operator_stack) {
    Operator *current = new Operator(infix[i]);
    if(current->is_operator())
        add_operator_to_stack(&postfix, operator_stack, current);
    else
        postfix += current->get_value();
}

string InfixToPostfix(string infix) {
    /*
    * If element is not an operator add to the postfix
    * else add to the stack
    * If there is a higher or equal priority operator at
    * the top of the stack, move top one to the postfix and add.
    * If a parenthesis becomes closed, add all operators between
    * parenthesis to the postfix
    * the last operators in stack should be added starting from top.
    */

    // Creating stacks
    string postfix = "";
    Stack<Operator> *operator_stack = new Stack<Operator>();
    Stack<Operator> *parenthesis_stack = new Stack<Operator>();

    // Parsing infix
    for(int i=0; i < infix.length(); i++) {
        InfixToPostfixChar(infix, postfix, i, operator_stack);
    }

    // Move remaining operators to postfix
    operator_stack->pop_all_to_string(&postfix);
    return postfix;
}

#endif