#include "syntax_validator.h"
#include <stdexcept>
#include <exceptions.h>
#include "error_reporter.h"
#include <iostream>
#include "highlight_manager.h"
using namespace std;

SyntaxValidator::SyntaxValidator(ErrorReporter& reporter, HighlightManager& highlight_manager) {
    this->error_reporter = &reporter;
    this->highlight_manager = &highlight_manager;
}

void SyntaxValidator::validate(ScriptLine &script_line) {
    const vector<Token*>& tokens = script_line.get_tokens();
    
    if (!are_parentheses_balanced(tokens))
        error_reporter->log(ErrorType::Syntax, "Unbalanced parentheses", tokens[0]->get_location());

    if (!are_quotes_balanced(tokens))
        error_reporter->log(ErrorType::Syntax, "Unbalanced string quotes", tokens[0]->get_location());

    for (auto const token : tokens) {
        check_token(tokens, token);
    }
}

bool SyntaxValidator::are_parentheses_balanced(const vector<Token*>& tokens) {
    Stack<Token*> stack;
    for (auto* token : tokens) {
        if (token->get_value() == "(") {
            stack.push(token);
        } else if (token->get_value() == ")") {
            if (stack.is_empty()) {
                return false; // Unmatched closing parenthesis
            }
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

void SyntaxValidator::check_token(vector<Token*> const tokens, const Token* token) {
    if (token->is_variable()) {
        const string& value = token->get_value();
        if (isdigit(value[0])) {
            error_reporter->log(ErrorType::Syntax, "Variable name cannot start with a digit: \n" +  highlight_manager->highlight_token(tokens, token), token->get_location());
        }
        
        for (char const &ch : value) {
            if (!isalnum(ch) && ch != '_') {
                error_reporter->log(ErrorType::Syntax, "Invalid character in variable name: " + value, token->get_location());
            }
        }
    }
    
    return;
}

// bool SyntaxValidator::is_valid_assignment() const {
//     if (!is_assignment() || tokens.empty())
//         return false;

//     if (!tokens[0]->is_variable())
//         return false;

//     if (tokens[1]->get_value() != "=")
//         return false;

//     if (tokens.size() < 3)
//         return false;

//     return true;
// }


// bool Token::is_valid_variable() const {
//     if (value.empty() || isdigit(value[0])) {
//         return false;
//     }

//     // Check that all characters are alphanumeric or underscore
//     for (char const &ch : value) {
//         if (!isalnum(ch) && ch != '_') {
//             return false;
//         }
//     }
//     return true;
// }