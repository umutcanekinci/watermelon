#pragma once
#include <string>

struct Location {
    std::string filename;
    int start_row;
    int end_row;
    int start_column;
    int end_column;

    Location(std::string filename = "", int line = -1, int column = -1, int start_column = -1, int end_column = -1);
    std::string to_string() const;
};