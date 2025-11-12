#pragma once
#include <vector>
#include <stdexcept>
#include "token.h"
#include "stack.h"

class ErrorReporter;
class HighlightManager;

class SyntaxValidator {
private:
    ErrorReporter *error_reporter;
    HighlightManager *highlight_manager;
public:
    SyntaxValidator(ErrorReporter& reporter, HighlightManager& highlight_manager);

    void validate(const std::vector<Token*>& tokens);

    bool are_parentheses_balanced(const std::vector<Token*>& tokens);

    bool are_quotes_balanced(const std::vector<Token*>& tokens);

    void check_token(std::vector<Token*> const tokens, const Token* token);

    void throw_error(const std::string& message, const Token& token);
};