#include "compiler.h"
#include "file_operations.h"

using namespace std;

int main() {
    Compiler* compiler = new Compiler();
    vector<string> output = compiler->compile_file("../tests/test.cpp");
    create_output_file("../tests/test.cpp", output);
    return 0;
}
