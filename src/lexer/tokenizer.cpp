#include "tokenizer.h"
#include "token.h"
#include "script_line.h"
#include "error_reporter.h"
#include <string>
using namespace std;

Tokenizer::Tokenizer(ErrorReporter& reporter) {
    this->error_reporter = &reporter;
}

vector<Token *> Tokenizer::tokenize(const ScriptLine& script_line) {
    vector<Token *> tokens;
    string buffer = "";
    string line = script_line.get_text();
    Location line_location = script_line.get_location();

    for (int i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (isspace(ch)) {
            flush_buffer(line, tokens, buffer, line_location, i+1);
            continue;
        }

        if (Token(ch).get_type() == OPERATOR) {
            flush_buffer(line, tokens, buffer, line_location, i+1);
            buffer += ch;
            flush_buffer(line, tokens, buffer, line_location, i+2);
            continue;
        }

        if (!buffer.empty()) {
            if (buffer.length() == 1 && isdigit(buffer[0]) && (!isdigit(ch) && ch != '.')) {
                Location token_location = Location(line_location, i, i);
                report_lex_error("Identifier name cannot start with a digit", token_location, line);
            }
        }

        buffer += ch;
    }
    flush_buffer(line, tokens, buffer, line_location, line.size()+1);
    return tokens;
}

void Tokenizer::flush_buffer(const string &line, vector<Token*>& tokens, string& buffer, Location& line_location, int end_col) {
    if (buffer.empty())
        return;

    bool unterminated_string = (buffer.length() >=2 && buffer.front() == '"' && !buffer.back() == '"');
    if (unterminated_string) {
        string message = "Unterminated string literal";
        int length = buffer.size();
        int start_column = end_col - length;
        Location token_location = Location(line_location, start_column, length);
        report_lex_error("Unterminated string literal", token_location, line);
    }
    else { 
        tokens.push_back(create_token(line, buffer, line_location, end_col));
    }

    buffer.clear();
}

Token *Tokenizer::create_token(const string &line, const string &value, Location &line_location, int end_column) {
    int length = value.size();
    int start_column = end_column - length;
    Location *location = new Location(line_location, start_column, length);
    Token *token = new Token(value, *location);
    return token;
}

void Tokenizer::report_lex_error(const std::string &message, const Location &loc, const std::string &line_text) {
    if (error_reporter) {
        error_reporter->log(ErrorType::Syntax, message, loc, line_text);
    } else {
        // fallback: print
        std::cerr << "Lex error: " << message << " at " << loc.to_string() << std::endl;
    }
}