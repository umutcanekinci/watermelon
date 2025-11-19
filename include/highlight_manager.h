#pragma once
#include <string>
#include <vector>

class Token;
class Location;

class HighlightManager {
public:
    std::string highlight(const std::string &line, const Location &location);
    std::string highlight_char(const std::string &line, size_t position);
    std::string highlight_string( const std::string &line, size_t start_pos, size_t length);
};