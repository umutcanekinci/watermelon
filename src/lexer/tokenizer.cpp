#include "tokenizer.h"
#include "token.h"
#include "script_line.h"

std::vector<Token *> Tokenizer::tokenize(const ScriptLine& script_line) {
    std::vector<Token *> tokens;
    std::string buffer = "";
    std::string line = script_line.get_text();
    Location line_location = script_line.get_location();

    for (int i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (isspace(ch)) {
            flush_buffer(tokens, buffer, line_location, i+1);
            continue;
        }
        
        if (Token(ch).is_operator()) {
            flush_buffer(tokens, buffer, line_location, i+1);
            tokens.push_back(create_token(std::string(1, ch), line_location, i+2));
            continue;
        }
        buffer += ch;
    }
    flush_buffer(tokens, buffer, line_location, line.size()+1);
    return tokens;
}

void Tokenizer::flush_buffer(std::vector<Token*>& tokens, std::string& buffer, Location& line_location, int end_col) {
    if (buffer.empty())
        return;

    tokens.push_back(create_token(buffer, line_location, end_col));
    buffer.clear();
}

Token *Tokenizer::create_token(const std::string &value, Location &line_location, int end_column) {
    int length = value.size();
    int start_column = end_column - length;
    Location *location = new Location(line_location, start_column, length);
    return new Token(value, *location);
}