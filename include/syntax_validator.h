#pragma once
#include <vector>
#include <stdexcept>
#include "token.h"
#include "stack.h"

class SyntaxValidator {
public:
    static void validate(const std::vector<Token*>& tokens);

    static bool are_parentheses_balanced(const std::vector<Token*>& tokens);

    static bool are_quotes_balanced(const std::vector<Token*>& tokens);

    static void check_token(const Token* token);

    static void throw_error(const std::string& message, const Token& token);
};