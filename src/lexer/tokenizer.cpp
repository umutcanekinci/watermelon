#include "tokenizer.h"
#include <cctype>
#include <iostream>

Tokenizer::Tokenizer(ErrorReporter &reporter)
    : error_reporter(&reporter)
{}

bool Tokenizer::is_operator_char(char c) const {
    const char *ops = "+-*/%=!<>&|^.,";
    return std::strchr(ops, c) != nullptr;
}

bool Tokenizer::is_multi_char_operator_start(char c) const {
    // e.g. '=', '!', '<', '>', '&', '|'
    return c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|';
}

std::vector<Token*> Tokenizer::tokenize(const ScriptLine &script_line) {
    std::vector<Token*> tokens;
    const std::string line = script_line.get_text();
    const Location base_loc = script_line.get_location();
    int n = (int)line.size();
    int i = 0;

    while (i < n) {
        char c = line[i];

        // whitespace
        if (std::isspace((unsigned char)c)) {
            ++i;
            continue;
        }

        // parentheses
        if (c == '(') {
            tokens.push_back(make_token_from_slice(line, i, i+1, base_loc));
            ++i;
            continue;
        }
        if (c == ')') {
            tokens.push_back(make_token_from_slice(line, i, i+1, base_loc));
            ++i;
            continue;
        }

        // comma
        if (c == ',') {
            tokens.push_back(make_token_from_slice(line, i, i+1, base_loc));
            ++i;
            continue;
        }

        // string literal
        if (c == '"') {
            scan_string(line, i, base_loc, tokens);
            continue;
        }

        // number literal (starts with digit or +/-, but careful: + could be operator)
        if (std::isdigit((unsigned char)c) || ((c == '+' || c == '-') && i+1 < n && std::isdigit((unsigned char)line[i+1]))) {
            scan_number(line, i, base_loc, tokens);
            continue;
        }

        // identifier or keyword (starts with letter or underscore)
        if (std::isalpha((unsigned char)c) || c == '_') {
            scan_identifier_or_keyword(line, i, base_loc, tokens);
            continue;
        }

        // operator
        if (is_operator_char(c)) {
            scan_operator(line, i, base_loc, tokens);
            continue;
        }

        // unknown character -> report lex error at this column
        Location err_loc(base_loc, i+1, 1);
        report_lex_error(std::string("Invalid character: '") + c + "'", err_loc, line);
        ++i;
    }

    // Optionally push EOF token
    // tokens.push_back(new Token("", Location(base_loc, n+1, 0)));

    return tokens;
}

Token* Tokenizer::make_token_from_slice(const std::string &line, int start_idx, int end_idx, const Location &base_loc) {
    int length = end_idx - start_idx;
    Location *loc = new Location(base_loc, start_idx+1, length); // start column 1-based
    std::string lexeme = line.substr(start_idx, length);
    Token *t = new Token(lexeme, *loc);
    if (t->get_type() == TokenType::Unknown) {
        // Unknown token: report lexical error
        report_lex_error("Invalid token: " + lexeme, *loc, line);
    }
    return t;
}

void Tokenizer::scan_string(const std::string &line, int &i, const Location &base_loc, std::vector<Token*> &out) {
    int start = i;
    ++i; // skip opening quote
    bool escaped = false;
    while (i < (int)line.size()) {
        char c = line[i];
        if (escaped) {
            escaped = false;
            ++i;
            continue;
        }
        if (c == '\\') {
            escaped = true;
            ++i;
            continue;
        }
        if (c == '"') {
            ++i; // include closing quote
            Token *t = make_token_from_slice(line, start, i, base_loc);
            out.push_back(t);
            return;
        }
        ++i;
    }
    // unterminated string
    Location err_loc(base_loc, start+1, 1);
    report_lex_error("Unterminated string literal", err_loc, line);
    // we can choose to create a token with the rest of line or skip — prefer to skip creating a bad token
}

void Tokenizer::scan_number(const std::string &line, int &i, const Location &base_loc, std::vector<Token*> &out) {
    int start = i;
    // optional leading sign
    if (line[i] == '+' || line[i] == '-') ++i;
    bool dot_seen = false;
    while (i < (int)line.size()) {
        char c = line[i];
        if (std::isdigit((unsigned char)c)) {
            ++i;
            continue;
        }
        if (c == '.') {
            if (dot_seen) break; // for now stop at second dot -> let make_token_from_slice report invalid if needed
            dot_seen = true;
            ++i;
            continue;
        }
        break;
    }
    Token *t = make_token_from_slice(line, start, i, base_loc);
    // additional number validation: make sure it's not something like "1..2"
    if (t->get_type() != TokenType::NumberLiteral) {
        report_lex_error("Invalid number literal: " + t->get_value(), t->get_location(), line);
    }
    out.push_back(t);
}

void Tokenizer::scan_identifier_or_keyword(const std::string &line, int &i, const Location &base_loc, std::vector<Token*> &out) {
    int start = i;
    while (i < (int)line.size()) {
        char c = line[i];
        if (std::isalnum((unsigned char)c) || c == '_') {
            ++i;
            continue;
        }
        break;
    }
    Token *t = make_token_from_slice(line, start, i, base_loc);
    // if the token is unknown (e.g. contains invalid characters), make_token_from_slice already reported
    out.push_back(t);
}

void Tokenizer::scan_operator(const std::string &line, int &i, const Location &base_loc, std::vector<Token*> &out) {
    // try multi-char operators first
    int start = i;
    char c = line[i];
    if (is_multi_char_operator_start(c) && i+1 < (int)line.size()) {
        std::string two = line.substr(i, 2);
        // list of 2-char ops: ==, !=, <=, >=, &&, ||
        if (two == "==" || two == "!=" || two == "<=" || two == ">=" || two == "&&" || two == "||") {
            i += 2;
            out.push_back(make_token_from_slice(line, start, i, base_loc));
            return;
        }
    }
    // single-char operator
    ++i;
    out.push_back(make_token_from_slice(line, start, i, base_loc));
}

void Tokenizer::report_lex_error(const std::string &message, const Location &loc, const std::string &line_text) {
    if (error_reporter) {
        error_reporter->log(ErrorType::Syntax, message, loc, line_text);
    } else {
        // fallback: print
        std::cerr << "Lex error: " << message << " at " << loc.to_string() << std::endl;
    }
}
