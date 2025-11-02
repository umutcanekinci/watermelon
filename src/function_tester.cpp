#include <iostream>
#include <string>
#include <vector>
#include "function_tester.h"
#include "file_operations.h"
using namespace std;

int FunctionTester::TEST_NUMBER = 0;

// Tests a single output against expected value and prints the result.
void FunctionTester::check_output(string input, string output, string expected) {
    cout << "Running Test #" << TEST_NUMBER << endl;
    if(output == expected) {
        cout << GREEN << "Test passed for  : " << input << endl << RESET;
        cout << GREEN << "Output           : " << output << endl << RESET;
    } else {
        cout << RED    << "Test failed for : " << input << endl << RESET;
        cout << BLUE   << "Expected        : " << expected << endl << RESET;
        cout << YELLOW << "Got             : " << output << endl << RESET;
    }
    cout << endl;
    TEST_NUMBER++;
}

void FunctionTester::test(vector<string> inputs, vector<string> expected_outputs, string (*func)(string)) {
    for (int i=0; i < inputs.size(); i++) {
        check_output(inputs[i], func(inputs[i]), expected_outputs[i]);
    }
}

void FunctionTester::test_with_file(string test_name, string (*func)(string)) {
    string folder_path = RESOURCES_PATH "../tests/infix_to_postfix_tests";
    string input_path = folder_path + "/input.txt";
    string expected_path = folder_path + "/expected.txt";
    vector<string> inputs = read_file(input_path);
    vector<string> expected_outputs = read_file(expected_path);
    test(inputs, expected_outputs, func);
}