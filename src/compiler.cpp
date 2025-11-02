#include <iostream>
#include <string>
#include <vector>
#include "compiler.h"
#include "file_operations.h"
#include "operator.h"
#include "token.h"
#include "script_line.h"
#include "stack.h"
#include "expression.h"
#include <stdexcept>
using namespace std;

string Compiler::compile_line(ScriptLine *line) {
    if (line->is_empty() || line->is_comment())
        return "";

    if (line->is_assignment()) {
        Token *variable_token = line->get_assignment_variable_token();
        string var_name = variable_token->get_value();
        Expression *expression = line->get_assignment_expression();
        expression->substitute_variables(variables);
        int result = expression->evaluate();
        // string postfix = expression->to_postfix();
        
        // Assignment handling
        for (auto& var : variables) {
            if (var.first == var_name) {
                cout << "----Updating variable " << var_name << " to value " << result << endl;
                var.second = result;
                return var_name + " = " + to_string(result) + "\n";
            }
        }
        cout << "----Creating variable " << var_name << " with value " << result << endl;
        variables.push_back(make_pair(var_name, result));
        return var_name + " = " + to_string(result) + "\n";
    }

    return "";
}

string Compiler::compile_file(string path) {
    string output = "";
    vector<string> input = read_file(path);
    for (int i=0; i < input.size(); i++) {
        string line = input[i];
        ScriptLine script_line(i+1, line);
        if (script_line.is_empty() || script_line.is_comment())
            continue;

        if (!script_line.is_valid())
            throw runtime_error("Syntax error in " + script_line.to_string());
        string result = compile_line(&script_line);
        if (result.empty())
            continue;

        output += result;
    }
    return output;
}