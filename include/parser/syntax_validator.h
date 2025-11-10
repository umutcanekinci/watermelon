#pragma once
#include <vector>
#include <stdexcept>
#include "token.h"
#include "stack.h"

class ErrorReporter;

class SyntaxValidator {
private:
    ErrorReporter *error_reporter;
public:
    SyntaxValidator(ErrorReporter& reporter);

    void validate(const std::vector<Token*>& tokens);

    bool are_parentheses_balanced(const std::vector<Token*>& tokens);

    bool are_quotes_balanced(const std::vector<Token*>& tokens);

    void check_token(const Token* token);

    void throw_error(const std::string& message, const Token& token);
};