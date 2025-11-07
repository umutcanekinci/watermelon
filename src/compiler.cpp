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
#include "memory.h"
using namespace std;

Compiler::Compiler() {
    memory = new Memory();
}

string Compiler::compile_line(ScriptLine *line) {
    if (line->is_empty() || line->is_comment())
        return "";

    if (line->is_assignment()) {
        string var_name = line->get_assignment_variable_token()->get_value();
        int result = line->get_assignment_expression()->substitute_variables(memory)->to_postfix()->evaluate();
        memory->set(var_name, result);
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