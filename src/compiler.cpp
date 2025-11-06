#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "compiler.h"
#include "file_operations.h"
#include "script_line.h"
#include "memory.h"
#include "expression.h"
#include "token.h"
#include "syntax_validator.h"
#include "tokenizer.h"
using namespace std;

Compiler::Compiler() {
    memory = new Memory();
    syntax_validator = new SyntaxValidator();
}

string Compiler::compile_file(string path) {
    string output = "";
    vector<string> input = read_file(path);
    for (int i=0; i < input.size(); i++) {
        string line = input[i];
        ScriptLine script_line(i+1, line);
        if (script_line.is_empty() || script_line.is_comment())
            continue;

        vector<Token *> tokens = Tokenizer::tokenize(line);

        syntax_validator->validate(tokens);

        compile_line(tokens);
    }

    return "";
}

string Compiler::compile_line(vector<Token *> tokens) {
    Expression infix = Expression(tokens);
    Expression *postfix = infix.to_postfix();

    cout << "[PARSE] Infix  : " << infix.to_string() << endl;
    cout << "[PARSE] Postfix: " << postfix->to_string() << endl;
    postfix->evaluate(memory);

    return "";
}