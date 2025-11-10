#include "compiler.h"
#include "file_operations.h"
#include <iostream>

using namespace std;

int main() {
    Compiler compiler;
    string input_path = RESOURCES_PATH "test.wm";
    string output = compiler.compile_and_run(input_path);
    
    vector<string> output_lines;
    size_t pos = 0;
    while ((pos = output.find('\n')) != string::npos) {
        output_lines.push_back(output.substr(0, pos));
        output.erase(0, pos + 1);
    }
    
    for (const auto& line : output_lines) {
        cout << line << endl;
    }

    return 0;
}