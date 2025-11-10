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
#include "error_reporter.h"
#include "exceptions.h"
#include "comment_remover.h"
using namespace std;

Compiler::Compiler() {
    memory = new Memory();
    syntax_validator = new SyntaxValidator();
    error_reporter = new ErrorReporter();
    tokens = vector<Token *>();
}

string Compiler::run() {
    string output = "";

    try {
        compile_line(tokens);    
    } catch (const Error& e) {
        error_reporter->log(ErrorType::Syntax, e.what(), script_line.get_location());
    }
    
    return output;
}

void Compiler::compile_file(string path) {
    vector<string> input = read_file(path);
    input = CommentRemover::remove_multiline_comment(input);

    for (int i=0; i < input.size(); i++) {
        string line = input[i];
        line = CommentRemover::remove_inline_comments(line);
        Location location(path, i+1, 1);
        ScriptLine script_line(location, line);

        if (script_line.is_empty())
            continue;

        vector<Token *> tokens = Tokenizer::tokenize(script_line);
        syntax_validator->validate(tokens);

    }

    error_reporter->display_errors();
}

void Compiler::compile_line(vector<Token *> tokens) {
    Expression infix = Expression(tokens);
    Expression *postfix = infix.to_postfix();

    cout << "[PARSE] Infix  : " << infix.to_string() << endl;
    cout << "[PARSE] Postfix: " << postfix->to_string() << endl;
    postfix->evaluate(memory);
}