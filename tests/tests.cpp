#ifndef TESTS_CPP
#define TESTS_CPP

#include <string>
#include <iostream>
#include <vector>
#include "../src/file_operations.cpp"

using namespace std;

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string BLUE = "\033[1;34m";
const string YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

int TEST_NUMBER = 0;
void test_function(string input, string expected, string (*func)(string)) {
    cout << "Test " << TEST_NUMBER << ": " << endl;
    string output = func(input);
    if(output == expected) {
        cout << GREEN << "Test passed for  : " << input << endl << RESET;
        cout << GREEN << "Output          : " << output << endl << RESET;
    } else {
        cout << RED    << "Test failed for : " << input << endl << RESET;
        cout << BLUE   << "Expected        : " << expected << endl << RESET;
        cout << YELLOW << "Got             : " << output << endl << RESET;
    }
    cout << endl;
    TEST_NUMBER++;
}


// This function evaluates the file lines with given function and write them to the output file.
void test_file(string path, string (*func)(string)) {
    vector<string> input = read_file(path);
    //vector<string> expected = read_file(expected_path);
    vector<string> output;
    for (int i=0; i < input.size(); i++) {
        // output.push_back(test_function(input[i], expected[i], func))
        output.push_back(func(input[i]));
    }
    create_output_file(path, output);
}

#endif"