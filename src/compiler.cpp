#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "compiler.h"
#include "file_operations.h"
#include "script_line.h"
#include "memory.h"
#include "expression.h"
#include "token.h"
using namespace std;

Compiler::Compiler() {
    memory = new Memory();
}

string Compiler::compile_file(string path) {
    string output = "";
    vector<string> input = read_file(path);
    for (int i=0; i < input.size(); i++) {
        string line = input[i];
        ScriptLine script_line(i+1, line);
        
        if (script_line.is_empty() || script_line.is_comment())
            continue;

        script_line.run(memory);
    }

    return "";
}