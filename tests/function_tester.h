#pragma once
#include <string>
#include <vector>

const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string BLUE = "\033[1;34m";
const std::string YELLOW = "\033[1;33m";
const std::string RESET = "\033[0m";

class FunctionTester {
private:
    static int TEST_NUMBER;
public:
    static void check_output(std::string input, std::string output, std::string expected);
    static void test(std::vector<std::string> inputs, std::vector<std::string> expected_outputs, std::string (*func)(std::string));
    static void test_with_file(std::string test_name, std::string (*func)(std::string));
};