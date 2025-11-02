#pragma once
#include <string>
#include <vector>
using namespace std;

vector<string> read_file(string path);
void create_output_file(string path, vector<string> lines);