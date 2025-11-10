#include "comment_remover.h"
#include <string>
using namespace std;

string CommentRemover::remove_inline_comments(const string& line) {
    size_t comment_pos = line.find("//");
    if (comment_pos != string::npos) {
        return line.substr(0, comment_pos);
    }
    return line;
}

vector<string> CommentRemover::remove_multiline_comment(const vector<string>& lines) {
    // Ensure not removing line completely in order to preserve line numbers.
    vector<string> result;
    bool in_comment_block = false;
    for (const auto& line : lines) {
        string new_line;
        size_t start = 0;
        while (start < line.length()) {
            if (!in_comment_block && line.substr(start, 2) == "/*") {
                in_comment_block = true;
                start += 2;
            } else if (in_comment_block && line.substr(start, 2) == "*/") {
                in_comment_block = false;
                start += 2;
            } else {
                if (!in_comment_block) {
                    new_line += line[start];
                }
                start++;
            }
        }
        result.push_back(new_line);
    }
    return result;
}
