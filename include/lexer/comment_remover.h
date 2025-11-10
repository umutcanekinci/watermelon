#pragma once
#include <string>
#include <vector>

class CommentRemover {
public:
    std::string remove_inline_comments(const std::string& line);
    std::vector<std::string> remove_multiline_comment(const std::vector<std::string>& lines);
};