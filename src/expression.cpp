#include <string>
#include "expression.h"
#include "token.h"
#include "stack.h"
#include "memory.h"
#include "operator_table.h"
#include "value.h"
using namespace std;

Expression::Expression(vector<Token *> tokens) {
    this->tokens = tokens;
}

Expression *Expression::to_postfix() {
    Stack<Token *> postfix;
    Stack<Token *> *operators = new Stack<Token *>();

    for(auto token : tokens) {
        if(token->is_operator()) {
            add_operator_to_stack(token, &postfix, operators);
            continue;
        }
        
        postfix.push(token);
    }

    operators->pop_all_to_other(&postfix); // Move remaining operators to postfix
    return new Expression(postfix.to_vector());
}

void Expression::add_operator_to_stack(Token *current, Stack<Token *> *postfix, Stack<Token *> *operator_stack) {
    // (, ) are dont have precedence but used in the algorithm, because they dont have oparation
    
    string current_value = current->get_value();

    // If stack is empty or current operator is (, just push it.
    if (operator_stack->is_empty() || current_value == "(") {
        operator_stack->push(current);
        return;
    }

    // If operator is closing parenthesis, all operators should popped to the string.
    Token *top = operator_stack->get();
    string top_value = top->get_value();

    if (current_value == ")") {
        if (top_value == "(") {
            operator_stack->pop();
            return;
        }

        operator_stack->pop_to_other(postfix);
        add_operator_to_stack(current, postfix, operator_stack);
        return;
    }

    if (top_value == "(") {
        operator_stack->push(current);
        return;
    }

    // Getting precedences
    auto current_presedence = OperatorTable::get(current_value)->precedence;
    auto top_precedence = OperatorTable::get(top_value)->precedence;

    // If current <= top, pop the top to the string and use recursion to check new top(s).
    if (current_presedence <= top_precedence) {
        operator_stack->pop_to_other(postfix);
        add_operator_to_stack(current, postfix, operator_stack);
        return;
    }

    operator_stack->push(current);
}

//int apply_operator(int operand1, char op, int operand2) {
Value apply_operator(const std::string &op, Value left, Value right, Memory* memory) {
    auto it = OperatorTable::get(op);
    return it->func(left, right, memory);
}

//int Expression::evaluate() {
Value Expression::evaluate(Memory *memory) {
    // TODO Assuming expression is in postfix notation
    // if not, give error or return later
    Stack<Value> values;

    for (auto token : tokens) {
        string token_value = token->get_value();
        if (!token->is_operator()) {
            Value val;
            if (token->is_number()) {
                if (token_value.find('.') != std::string::npos)
                    val = Value(std::stof(token_value));
                else
                    val = Value(std::stoi(token_value));
            } else if (token->is_bool()) {
                val = Value(token_value == "true");
            } else if (token->is_string()) {
                val = Value(token_value.substr(1, token_value.length() - 2)); // remove quotes
            } else if (token->is_variable()) {
                val = Value::make_reference(token_value);
            } else {
                throw std::runtime_error("Unknown token: " + token_value);
            }

            values.push(val);
            continue;
        }

        // operator
        Value right = values.pop();
        Value left = values.pop();

        // Eğer op özel değilse ve operandlar reference ise, apply_operator içindeki lambda'lar
        // genelde gerçek değerlere ihtiyaç duyacağından burada onları çözüp gönderebilirsin.
        // Ancak assignment (=) için lhs referans olarak kalmalı; bu yüzden op'a göre davran.

        // assign_op kendisi reference kontrolünü yapar
        // Diğer operatörler için reference'ları resolve et:
        if (token_value != "=") {
            if (left.is_reference()) {
                Value tmp = memory->get(left.as_variable_name());
                if (tmp.is_null())
                    throw std::runtime_error("Undefined variable: " + left.as_variable_name());
                left = tmp;
            }
            if (right.is_reference()) {
                Value tmp = memory->get(right.as_variable_name());
                if (tmp.is_null())
                    throw std::runtime_error("Undefined variable: " + right.as_variable_name());
                right = tmp;
            }
        }
        Value result = apply_operator(token_value, left, right, memory);
        values.push(result);
    }

    return values.pop();
}

bool Expression::are_parentheses_balanced(string &infix) {
    return true;
    
    // Stack<Token> parenthesis_stack = Stack<Token>();

    // for (auto ch : infix) {
    //     Token character = Token(string(1, ch));
    //     if (character.get_value() == "(")
    //         parenthesis_stack.push(character);
    //     else if (character.get_value() == ")") {
    //         if (parenthesis_stack.is_empty() || parenthesis_stack.get().get_value() != "(")
    //             return false;
    //         parenthesis_stack.pop();
    //     }
    // }
    // return parenthesis_stack.is_empty();
}

string Expression::to_string() const {
    string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result += tokens[i]->get_value();
        if (i != tokens.size() - 1)
            result += " ";
    }
    return result;
}