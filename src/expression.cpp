#include <string>
#include "expression.h"
#include "token.h"
#include "operator.h"
#include "stack.h"
#include "memory.h"
using namespace std;

Expression::Expression(vector<Token *> tokens) {
    this->tokens = tokens;
}

Expression *Expression::substitute_variables(Memory *memory) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token* token = tokens[i];
        if (!token)
            continue;
        if (token->get_type() == Token::VARIABLE) {
            auto value = memory->get(token->get_value());
            if (value != NULL) {
                token->set_value(std::to_string(value));
            }
        }
    }
    return this;
}

int char_to_operator(int operand1, char op, int operand2) {
    cout << "Evaluating: " << operand2 << " " << op << " " << operand1 << endl;
    
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
            value_stack->push(&value); // TODO
            continue;
        }

        if (value_stack->is_empty() || value_stack->length() < 2)
            throw std::runtime_error("Invalid expression");

        int val1 = *value_stack->pop();
        int val2 = *value_stack->pop();

        int result = char_to_operator(val2, character->get_value()[0], val1);

        value_stack->push(&result);
    }

    return *value_stack->pop();
}

bool Expression::check_parenthesis(string &infix) {
    Stack<Operator> parenthesis_stack = Stack<Operator>();

    for (int i=0; i<infix.length(); i++) {
        Operator character = Operator(infix[i]);
        if (character == '(')
            parenthesis_stack.push(&character);
        else if (character == ')') {
            if (parenthesis_stack.is_empty() || parenthesis_stack.get()->get_value() != '(')
                return false;
            parenthesis_stack.pop();
        }
    }
    return parenthesis_stack.is_empty();
}

void Expression::add_operator_to_stack(vector<Token *> *postfix, Stack<Operator> *operator_stack, Operator *current) {

    // If stack is empty or current operator is (, just push it.
    if (operator_stack->is_empty() || *current == '(') {        
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
        //operator_stack->pop_to_string(postfix);
        postfix->push_back(new Token(string(1, operator_stack->pop()->get_value())));
        add_operator_to_stack(postfix, operator_stack, current);
        return;
    }

    // If current <= top, pop the top to the string and use recursion to check new top(s).
    if (current->get_priority() >= top->get_priority()) {
        if (*top == '(') {
            operator_stack->push(current);
            return;
        }

        //operator_stack->pop_to_string(postfix);
        postfix->push_back(new Token(string(1, operator_stack->pop()->get_value())));
        add_operator_to_stack(postfix, operator_stack, current);
        return;
    }

    operator_stack->push(current);
}

void Expression::infix_to_postfix_char(Token *current, vector<Token *> &postfix, int i, Stack<Operator> *operator_stack) {
    if(current->is_operator())
        add_operator_to_stack(&postfix, operator_stack, new Operator(current->get_value()[0]));
    else
        postfix.push_back(current);
}

Expression *Expression::to_postfix() {
    // Creating stacks
    vector<Token *> postfix;
    Stack<Operator> *operator_stack = new Stack<Operator>();

    // Parsing infix
    for(int i=0; i < tokens.size(); i++) {
        Token* token = tokens[i];
        infix_to_postfix_char(token, postfix, i, operator_stack);
    }

    // Move remaining operators to postfix
    //operator_stack->pop_all_to_string(&postfix);
    for (; !operator_stack->is_empty(); ) {
        postfix.push_back(new Token(string(1, operator_stack->pop()->get_value())));
    }
    
    return new Expression(postfix);
}

string Expression::to_string() const {
    string result = "";
    for (const auto& token : tokens) {
        result += token->get_value();
    }
    return result;
}