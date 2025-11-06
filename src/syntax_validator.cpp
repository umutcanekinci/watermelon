#include "syntax_validator.h"
#include <stdexcept>

void SyntaxValidator::validate(const std::vector<Token*>& tokens) {
        if (!are_parentheses_balanced(tokens))
            throw std::runtime_error("Unbalanced parentheses");

        if (!are_quotes_balanced(tokens))
            throw std::runtime_error("Unbalanced string quotes");

        for (auto const token : tokens) {
            check_token(token);
        }
    }

bool SyntaxValidator::are_parentheses_balanced(const std::vector<Token*>& tokens) {
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

bool SyntaxValidator::are_quotes_balanced(const std::vector<Token*>& tokens) {
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

void SyntaxValidator::check_token(const Token* token) {
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
//     if (value.empty() || std::isdigit(value[0])) {
//         return false;
//     }

//     // Check that all characters are alphanumeric or underscore
//     for (char const &ch : value) {
//         if (!std::isalnum(ch) && ch != '_') {
//             return false;
//         }
//     }
//     return true;
// }