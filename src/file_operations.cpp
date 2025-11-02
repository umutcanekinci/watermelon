#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file_operations.h"
using namespace std;

vector<string> read_file(string path) {
    vector<string> lines;
    ifstream file(path);

    if (!file) {
        cout << "An unexpected error occurred while opening the file with path " << path << endl;
        return lines;
    }
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

void create_output_file(string path, vector<string> lines) {
    path = path.substr(0, path.find_last_of('.')) + "_output" + path.substr(path.find_last_of('.'));
    ofstream file(path);

    for (size_t i = 0; i < lines.size(); i++) {
        file << lines[i] << endl;
    }

    file.close();
}