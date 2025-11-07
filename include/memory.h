#pragma once
#include <string>
#include <unordered_map>

class Memory {
public:
    Memory();
    int get(const std::string& name) const;
    void set(const std::string& name, int value);   
private:
    std::unordered_map<std::string, int> variables;
};