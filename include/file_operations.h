#pragma once
#include <string>
#include <vector>

std::vector<std::string> read_file(std::string path);
void create_output_file(std::string path, std::vector<std::string> lines);