#include <string>
#include "highlight_manager.h"
#include "script_line.h"
#include "token.h"
using namespace std;

string HighlightManager::highlight_token(vector<Token *> tokens, const Token *token) {
    string line;
    for (auto const t : tokens) {
        line += t->get_value();
    }
    return highlight_string(line, token->get_location().get_start_pos(), token->get_value().length());
}

string HighlightManager::highlight_string(std::string &line, size_t start_pos, size_t length) {
    // Implementation for highlighting a substring within a string
    // This is a placeholder implementation
    std::string highlighted(line.size(), ' ');
    for (size_t i = start_pos; i < start_pos + length && i < line.size(); ++i) {
        highlighted[i] = '^';
    }
    return line + "\n" + highlighted;
}