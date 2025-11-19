#include "location.h"
#include <string>
using namespace std;

Location::Location(Location const& other, int start_column, int length) {
    this->filename = other.filename;
    this->line_number = other.line_number;
    this->start_column = start_column;
    this->length = length;
}

Location::Location(string filename, int line_number) {
    this->filename = filename;
    this->line_number = line_number;
    this->start_column = -1;
    this->length = -1;
}

Location::Location(string filename, int line_number, int start_column, int length) {
    this->filename = filename;
    this->line_number = line_number;
    this->start_column = start_column;
    this->length = length;
}

int Location::get_line_number() const {
    return line_number;
}

int Location::get_start_pos() const {
    return start_column;
}

int Location::get_length() const {
    return length;
}

string Location::to_string() const {
    return filename + ":" + std::to_string(line_number) + ":" + std::to_string(start_column) + "-" + std::to_string(start_column + length);
}