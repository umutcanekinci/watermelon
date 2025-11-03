#pragma once
#include <string>
#include <vector>

class Memory;
class Token;
class Expression;

class ScriptLine {
private:
    int number;
    std::string line;
    std::vector<Token *> tokens;
public:
    ScriptLine(int number, const std::string& line);
    bool is_comment() const;
    bool is_empty() const;
    bool is_assignment() const;
    bool is_valid() const;
    bool is_valid_assignment() const;
    void tokenize();
    void substitute_variables(const std::vector<std::pair<std::string, int>>& variables);
    std::pair<std::string, int> get_assignment_variable_and_value(Memory *memory);
    Token *get_assignment_variable_token();
    Expression *get_assignment_expression();
    std::string to_string() const;
};
