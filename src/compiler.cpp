#ifndef COMPILER_CPP
#define COMPILER_CPP

#include <string>
#include <vector>
#include "file_operations.cpp"
#include "infix_to_postfix.cpp"

using namespace std;

class Compiler {
    vector<pair<string, int>> variables;

public:
    bool is_number(const string& s) {
        for (char const &ch : s) {
            if (std::isdigit(ch) == 0) return false;
        }
        return true;
    }

    int code_to_value(const string& code) {                 
        for (auto& var : variables) {
            if (var.first == code) {
                return var.second;
            }
        }
        throw "Undefined variable: " + code;
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
                    throw "Division by zero";
                }

                return operand2 / operand1;
            
            default:
                return 0;
        }
    }

    int evaluate_postfix(string postfix) {
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

    string compile_line(const string& sourceCode) {
        if (sourceCode.empty() || sourceCode.substr(0, 2) == "//")
            return "";

        if (sourceCode.find('=') != string::npos) {
            size_t equalPos = sourceCode.find('=');
            string varName = sourceCode.substr(0, equalPos);
            string expression = sourceCode.substr(equalPos + 1);

            string postfix = InfixToPostfix(expression);
            int result = evaluate_postfix(postfix);

            variables.push_back(make_pair(varName, result));
            return varName + " = " + to_string(result);
        }

        string out = InfixToPostfix(sourceCode);

        return out;
    }

    vector<string> compile_file(string path) {
        vector<string> output;

        vector<string> input = read_file(path);
        for (int i=0; i < input.size(); i++) {
            string compiled_line = compile_line(input[i]);
            if (!compiled_line.empty()) {
                output.push_back(compiled_line);
            }
        }

        return output;
    }
};


#endif