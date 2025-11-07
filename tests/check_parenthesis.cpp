#include <string>
#include "operator.h"
#include "stack.h"
using namespace std;

bool check_parenthesis(string &infix) {
    Stack<Operator> *parenthesis_stack = new Stack<Operator>();

    for (int i=0; i<infix.length(); i++) {
        Operator* character = new Operator(infix[i]);
        if (*character == '(')
            parenthesis_stack->push(character);
        else if (*character == ')') {
            if (parenthesis_stack->is_empty() || *parenthesis_stack->get() != '(')
                return false;
            parenthesis_stack->pop();
        }
    }
    return parenthesis_stack->is_empty();
}