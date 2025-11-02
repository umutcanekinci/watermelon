#pragma once
#include <string>
#include <vector>
using namespace std;

class ScriptLine;

class Compiler {
    vector<pair<string, int>> variables;
public:
    bool is_number(const string& s);
    int code_to_value(const string& code);
    int char_to_operator(int operand1, char op, int operand2);
    int evaluate_postfix(string postfix);
    string compile_line(const string& sourceCode);
    vector<string> compile_file(string path);
    vector<string> swap_variables_with_values(const vector<string>& tokens, const vector<pair<string, int>>& variables);
    string compile_line(ScriptLine line);
};