#pragma once
#include <string>

struct Location {
    std::string filename;
    int line;
    int column;

    Location(std::string filename = "", int line = -1, int column = -1);
    std::string to_string() const;
};