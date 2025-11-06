#include "script_line.h"
#include "token.h"
#include "expression.h"
#include <stdexcept>
#include <string>
#include <value.h>
using namespace std;

ScriptLine::ScriptLine(int number, const string& line) {
    this->number = number;
    this->line = line;
    tokenize();
}

/* Parse line to the operators, numbers, and variables */
void ScriptLine::tokenize() {
    string current_token = "";
    for (char ch : line) {
        if (isspace(ch))
            continue;

        Token token(string(1, ch));
        if (token.is_operator()) {
            if (!current_token.empty()) {
                token.set_value(current_token);
                tokens.push_back(new Token(current_token));
            }
            tokens.push_back(new Token(string(1, ch)));
            current_token = "";
            continue;
        }
        current_token += ch;
    }
    if (current_token.empty())
        return;
    
    tokens.push_back(new Token(current_token));
}

bool ScriptLine::is_comment() const {
    return line.rfind("//", 0) == 0; 
}

bool ScriptLine::is_empty() const {
    return line.empty();
}

// Invalid lines should print error during compilation
bool ScriptLine::is_valid() const {
    // Check assignment validity
    if (is_assignment() && !is_valid_assignment())
        return false;
     
    // Check variable naming
    for (const Token* token : tokens) {
        if (token->is_variable() && !token->is_valid_variable())
            return false;
    }

    return true;
}

bool ScriptLine::is_assignment() const {
    return !is_empty() && !is_comment() && line.find('=') != string::npos;
}

bool ScriptLine::is_valid_assignment() const {
    if (!is_assignment() || tokens.empty())
        return false;

    if (!tokens[0]->is_variable())
        return false;

    if (tokens[1]->get_value() != "=")
        return false;

    if (tokens.size() < 3)
        return false;

    return true;
}

void ScriptLine::run(Memory *memory) {
    Expression infix = Expression(tokens);
    cout << "[PARSE] Infix  : " << infix.to_string() << endl;
    Expression *postfix = infix.to_postfix();
    cout << "[PARSE] Postfix: " << postfix->to_string() << endl;
    postfix->evaluate(memory);
}

string ScriptLine::to_string() const {
    string result = "Line " + std::to_string(number) + ": ";
    for (Token* token : tokens) {
        if (token) {
            result += token->get_value();
        }
    }
    return result;
}