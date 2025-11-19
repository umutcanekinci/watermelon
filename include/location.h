#pragma once
#include <string>

/*

start_column -> inclusive

*/
struct Location {
    std::string filename;
    int line_number;
    int start_column;
    int length;

    Location(Location const&, int start_column, int length);
    Location(std::string filename, int line_number);
    Location(std::string filename = "", int line = -1, int start_column = -1, int length = -1);
    int get_line_number() const;
    int get_start_pos() const;
    int get_length() const;
    std::string to_string() const;
};