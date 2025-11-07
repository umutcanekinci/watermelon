#include "location.h"
#include <string>
using namespace std;

Location::Location(string filename, int line, int column) {
    this->filename = std::move(filename);
    this->line = line;
    this->column = column;
}

string Location::to_string() const {
    return filename + ":" + std::to_string(line) + ":" + std::to_string(column);
}