#include <string>
#include "highlight_manager.h"
#include "script_line.h"
#include "token.h"
using namespace std;

string HighlightManager::highlight(const string& line, const Location &location) {
    int start_pos = location.get_start_pos();
    int length = location.get_length();
    return highlight_string(line, start_pos, length);
}

string HighlightManager::highlight_string(const string &line, size_t start_pos, size_t length) {
    std::string highlighted(line.size(), ' ');
    for (size_t i = start_pos - 1; i < start_pos + length - 1 && i < line.size(); ++i) {
        highlighted[i] = '^';
    }
    return line + "\n" + highlighted;
}