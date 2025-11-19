#include "script_line.h"
#include "token.h"
#include "expression.h"
#include <stdexcept>
#include <string>
#include <value.h>
#include "comment_remover.h"
#include "tokenizer.h"
#include "syntax_validator.h"
using namespace std;

ScriptLine::ScriptLine(const Location& location, const string& line) {
    this->location = location;
    this->line = line;
    this->tokens = vector<Token *>();
}

string ScriptLine::get_text() const {
    return line;
}

Location ScriptLine::get_location() const {
    return location;
}

vector<Token *> ScriptLine::get_tokens() const {
    return tokens;
}

Expression* ScriptLine::get_expression() const {
    return expression;
}

void ScriptLine::remove_comments(CommentRemover &remover) {
    line = remover.remove_inline_comments(line);
}

bool ScriptLine::is_empty() const {
    return line.empty();
}

void ScriptLine::compile(CommentRemover &remover, Tokenizer &tokenizer, SyntaxValidator &validator) {
    remove_comments(remover);
    tokenize(tokenizer);
    validate(validator);
    compile_expression();
}

void ScriptLine::tokenize(Tokenizer &tokenizer) {
    tokens = tokenizer.tokenize(*this);
}

void ScriptLine::validate(SyntaxValidator &validator) {
    validator.validate(*this);
}

void ScriptLine::compile_expression() {
    // cout << "[PARSE] Infix  : " << infix.to_string() << endl;
    // cout << "[PARSE] Postfix: " << postfix->to_string() << endl;
    
    expression = new Expression(tokens);
    expression = expression->to_postfix();
}

void ScriptLine::run(Memory &memory) {
    expression->evaluate(&memory);
}

string ScriptLine::to_string() const {
    return location.to_string() + " " + line;
}