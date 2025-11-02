#include "compiler.h"
#include "file_operations.h"
#include "infix_to_postfix.h"
#include "function_tester.h"

using namespace std;


int main() {
    Compiler* compiler = new Compiler();
    string input_path = RESOURCES_PATH "test.cpp";
    vector<string> output = compiler->compile_file(input_path);
    create_output_file(input_path, output);

    return 0;
}