#pragma once
#include <string>
#include <vector>
#include "value.h"
#include "location.h"

class Memory;
class Token;
class Expression;
class Tokenizer;
class CommentRemover;
class SyntaxValidator;

class ScriptLine {
private:
    std::string line;
    Location location;
    std::vector<Token *> tokens;
    Expression* expression;
public:
    ScriptLine(const Location& location, const std::string& line);

    std::string get_text() const;
    Location get_location() const;
    std::vector<Token *> get_tokens() const;
    Expression* get_expression() const;
    std::string to_string() const;
    
    void compile(CommentRemover &remover, Tokenizer &tokenizer, SyntaxValidator &validator);
    void remove_comments(CommentRemover &remover);
    bool is_empty() const;
    void tokenize(Tokenizer &tokenizer);
    void validate(SyntaxValidator &validator);
    void compile_expression();    
    void run(Memory &memory);
};
