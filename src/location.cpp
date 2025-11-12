#include "location.h"
#include <string>
using namespace std;

Location::Location(string filename, int line, int column

Location::Location(string filename, int line, int column, int start_column, int end_column) {
    this->filename = filename;
    this->line = line;
    this->column = column;
    this->start_column = start_column;
    this->end_column = end_column;
}

string Location::to_string() const {
    return filename + ":" + to_string(line) + ":" + to_string(column);
}