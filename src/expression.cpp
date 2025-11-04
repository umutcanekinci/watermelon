#include <string>
#include "expression.h"
#include "token.h"
#include "stack.h"
#include "memory.h"
using namespace std;

Expression::Expression(vector<Token *> tokens) {
    this->tokens = tokens;
}

Expression *Expression::to_postfix() {
    Stack<Token *> postfix;
    Stack<Token *> *operator_stack = new Stack<Token *>();

    for(int i=0; i < tokens.size(); i++) {
        Token* token = tokens[i];
        if(token->is_operator()) {
            add_operator_to_stack(token, &postfix, operator_stack);
            continue;
        }
        
        postfix.push(token);
    }

    // Move remaining operators to postfix
    operator_stack->pop_all_to_other(&postfix);
    return new Expression(postfix.to_vector());
}

void Expression::add_operator_to_stack(Token *current, Stack<Token *> *postfix, Stack<Token *> *operator_stack) {
 
    // If stack is empty or current operator is (, just push it.
    if (operator_stack->is_empty() || current->get_value() == "(") {
        operator_stack->push(current);
        return;
    }

    // If operator is closing parenthesis, all operators should popped to the string.
    Token *top = operator_stack->get();
    
    if (current->get_value() == ")") {
        if (top->get_value() == "(") {
            operator_stack->pop();
            return;
        }

        operator_stack->pop_to_other(postfix);
        add_operator_to_stack(current, postfix, operator_stack);
        return;
    }

    // If current <= top, pop the top to the string and use recursion to check new top(s).
    if (current->get_precedence() >= top->get_precedence()) {
        if (top->get_value() == "(") {
            operator_stack->push(current);
            return;
        }

        operator_stack->pop_to_other(postfix);
        add_operator_to_stack(current, postfix, operator_stack);
        return;
    }

    operator_stack->push(current);
}

Expression *Expression::substitute_variables(Memory *memory) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token* token = tokens[i];
        if (!token)
            continue;

        if (token->is_variable()) {
            auto value = memory->get(token->get_value());
            if (value != NULL) {
                token->set_value(std::to_string(value));
            }
        }
    }
    return this;
}

int Expression::evaluate() {
    // TODO Assuming expression is in postfix notation
    // if not, give error or return later

    Stack<int> *value_stack = new Stack<int>();

    for (int i=0; i<tokens.size(); i++) {
        Token* character = tokens[i];
        if (!character->is_operator()) {
            if (!character->is_number())
                throw std::runtime_error("Unknown variable in expression " + to_string());

            int value = std::stoi(character->get_value());
            value_stack->push(value);
            continue;
        }

        if (value_stack->is_empty() || value_stack->length() < 2)
            throw std::runtime_error("Invalid expression");

        int val1 = value_stack->pop();
        int val2 = value_stack->pop();

        int result = apply_operator(val2, character->get_value()[0], val1);

        value_stack->push(result);
    }

    return value_stack->pop();
}

int apply_operator(int operand1, char op, int operand2) {
    cout << "Evaluating: " << operand2 << " " << op << " " << operand1 << endl;
    // operator_string, operator_precedence, operator_func
    switch (op)
    {
        case '+':
            return operand2 + operand1;

        case '-':
            return operand2 - operand1;
            
        case '*':
            return operand2 * operand1;

        case '/':
            if (operand1 == 0) {
                throw std::runtime_error("Division by zero");
            }

            return operand2 / operand1;
            
        default:
            return 0;
    }
}

bool Expression::check_parenthesis(string &infix) {
    Stack<Token *> parenthesis_stack = Stack<Token *>();

    for (int i=0; i<infix.length(); i++) {
        Token *character = new Token(string(1, infix[i]));
        if (character->get_value() == "(")
            parenthesis_stack.push(character);
        else if (character->get_value() == ")") {
            if (parenthesis_stack.is_empty() || parenthesis_stack.get()->get_value() != "(")
                return false;
            parenthesis_stack.pop();
        }
    }
    return parenthesis_stack.is_empty();
}

string Expression::to_string() const {
    string result = "";
    for (const auto& token : tokens) {
        result += token->get_value();
    }
    return result;
}