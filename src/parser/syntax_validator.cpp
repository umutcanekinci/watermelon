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
        check_token(line, token);
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

void SyntaxValidator::check_token(const string& line, const Token* token) {
    if (token->is_variable()) {
        const string& value = token->get_value();
        Location token_location = token->get_location();
        int start_pos = token_location.get_start_pos();
        
        if (isdigit(value[0])) {
            Location error_location = Location(token_location, start_pos, 1);
            error_reporter->log(ErrorType::Syntax, "Variable name cannot start with a digit", error_location, line);
        }
        
        for (int i = 0; i < value.size(); i++) {
            char ch = value[i];
            if (!isalnum(ch) && ch != '_') {
                Location error_location = Location(token_location, start_pos + i, 1);
                error_reporter->log(ErrorType::Syntax, "Invalid character in variable name", error_location, line);
            }
        }
    }
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