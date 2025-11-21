#include "syntax_validator.h"
#include <stdexcept>
#include <exceptions.h>
#include "error_reporter.h"
#include <iostream>
#include "script_line.h"
using namespace std;

SyntaxValidator::SyntaxValidator(ErrorReporter& reporter) {
    this->error_reporter = &reporter;
}

void SyntaxValidator::validate(ScriptLine &script_line) {
    string line = script_line.get_text();
    const vector<Token*>& tokens = script_line.get_tokens();
    Location location = script_line.get_location();
    if (!are_parentheses_balanced(tokens))
        error_reporter->log(ErrorType::Syntax, "Unbalanced parentheses", location, line);

    if (!are_quotes_balanced(tokens))
        error_reporter->log(ErrorType::Syntax, "Unbalanced string quotes", location, line);

    for (auto const token : tokens) {
        validate_token(line, token);
    }
}

bool SyntaxValidator::are_parentheses_balanced(const vector<Token*>& tokens) {
    Stack<Token*> stack;
    for (auto* token : tokens) {
        if (token->get_value() == "(") {
            stack.push(token);
        } else if (token->get_value() == ")") {
            if (stack.is_empty())
                return false;
            stack.pop();
        }
    }
    return stack.is_empty();
}

bool SyntaxValidator::are_quotes_balanced(const vector<Token*>& tokens) {
    int quote_count = 0;
    for (auto* token : tokens) {
        for (char ch : token->get_value()) {
            if (ch == '"') {
                quote_count++;
            }
        }
    }
    return quote_count % 2 == 0;
}

void SyntaxValidator::validate_token(const string& line, const Token* token) { 

    // if (token->is_variable()) {
    //     validate_variable(line, token);
    // }
    // else if (token->is_number()) {
    //     validate_number(line, token);
    // }
}