#pragma once
#include <string>
#include <unordered_map>

class Memory {
public:
    Memory();
    int get(const std::string& name) const;
    void set(const std::string& name, int value);   
    void set(std::pair<std::string, int> var_and_value);
private:
    std::unordered_map<std::string, int> variables;
};