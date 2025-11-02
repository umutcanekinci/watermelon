#pragma once
#include <string>
#include <vector>
using namespace std;

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string BLUE = "\033[1;34m";
const string YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

class FunctionTester {
private:
    static int TEST_NUMBER;
public:
    static void check_output(string input, string output, string expected);
    static void test(vector<string> inputs, vector<string> expected_outputs, string (*func)(string));
    static void test_with_file(string test_name, string (*func)(string));
};