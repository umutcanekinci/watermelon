#include "tokenizer.h"
#include "token.h"
#include "script_line.h"

std::vector<Token *> Tokenizer::tokenize(const ScriptLine& script_line) {
    Location location = script_line.get_location();
    std::vector<Token *> tokens;
    std::string buffer = "";
    for (char ch : script_line.get_text()) {
        if (isspace(ch))
            continue;

        Token *token = new Token(ch, location);
        if (token->is_operator()) {
            if (!buffer.empty()) {
                tokens.push_back(new Token(buffer, location));
            }
            tokens.push_back(token);
            buffer = "";
            continue;
        }
        buffer += ch;
    }

    if (buffer.empty())
        return tokens;
    
    tokens.push_back(new Token(buffer, location));
    return tokens;

}