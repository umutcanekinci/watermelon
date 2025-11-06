#include "tokenizer.h"
#include "token.h"

std::vector<Token *> Tokenizer::tokenize(const std::string& line) {
    std::vector<Token *> tokens;
    std::string buffer = "";
    for (char ch : line) {
        if (isspace(ch))
            continue;

        Token *token = new Token(ch);
        if (token->is_operator()) {
            if (!buffer.empty()) {
                tokens.push_back(new Token(buffer));
            }
            tokens.push_back(token);
            buffer = "";
            continue;
        }
        buffer += ch;
    }

    if (buffer.empty())
        return tokens;
    
    tokens.push_back(new Token(buffer));
    return tokens;

}