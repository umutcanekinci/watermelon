#include <iostream>
#include <string>
#include <vector>
#include "compiler.h"
#include "file_operations.h"
#include "infix_to_postfix.h"
#include "operator.h"
#include "token.h"
#include "script_line.h"

using namespace std;

bool Compiler::is_number(const string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

int Compiler::code_to_value(const string& code) {
    for (auto& var : variables) {
        if (var.first == code) {
            return var.second;
        }
    }
    throw "Undefined variable: " + code;
}

int Compiler::char_to_operator(int operand1, char op, int operand2) {
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
                throw "Division by zero";
            }

            return operand2 / operand1;
        
        default:
            return 0;
    }
}

int Compiler::evaluate_postfix(string postfix) {
    cout << "Evaluating postfix: " << postfix << endl;
    Stack<int> *value_stack = new Stack<int>();

    Operator* character;
    for (int i=0; i < postfix.size(); i++) {
        
        character = new Operator(postfix[i]);
        if (!character->is_operator()) {
            int value = is_number(string(1, postfix[i])) ? (postfix[i] - '0') : code_to_value(string(1, postfix[i]));
            cout << "Pushing value: " << value << endl;
            value_stack->push(&value);
            continue;
        }

        if (value_stack->is_empty() || value_stack->length() < 2)
            throw "Invalid expression";

        int val1 = *value_stack->pop();
        int val2 = *value_stack->pop();

        int result = char_to_operator(val2, character->get_value(), val1);

        value_stack->push(&result);
    }

    return *value_stack->pop();
}

string Compiler::evaluate_line(vector<string> sourceCode) {
    if (sourceCode.empty())
        return "";

    if (sourceCode.find('=') != string::npos) {
        size_t equalPos = sourceCode.find('=');
        string varName = sourceCode.substr(0, equalPos);
        string expression = sourceCode.substr(equalPos + 1);

        string postfix = infix_to_postfix(expression);
        int result = evaluate_postfix(postfix);

        variables.push_back(make_pair(varName, result));
        return varName + " = " + to_string(result);
    }

    string out = infix_to_postfix(sourceCode);

    return out;
}

int get_variable_value(const string& varName, const vector<pair<string, int>>& variables) {
    for (const auto& var : variables) {
        if (var.first == varName) {
            return var.second;
        }
    }
    return NULL;
}

// Need to swap variables with their values before evaluating
vector<string> swap_variables_with_values(const vector<string>& tokens, const vector<pair<string, int>>& variables) {
    vector<string> swapped;
    for (const string& token : tokens) {
        int value = get_variable_value(token, variables);
        if (value != NULL) {
            swapped.push_back(to_string(value));
            continue;
        }

        swapped.push_back(token);
    }
    return swapped;
}


string Compiler::compile_line(ScriptLine line) {
    vector<string> tokenized_line = line.tokenize();

    string compiled_line = evaluate_line(swap_variables_with_values(tokenize(line), variables));
    if (compiled_line.empty())
        return "";

    return compiled_line;
}

vector<string> Compiler::compile_file(string path) {
    vector<string> output, input = read_file(path);
    for (int i=0; i < input.size(); i++) {
        string line = input[i];
        ScriptLine script_line(line);
        if (script_line.is_empty() || script_line.is_comment())
            continue;

        string result = compile_line(script_line);
        if (result.empty())
            continue;

        output.push_back(result);
    }
    return output;
}