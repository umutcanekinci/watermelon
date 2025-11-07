#pragma once
#include <string>
#include <unordered_map>

class Value;

class Memory {
public:
    Memory();
    Value get(const std::string& name) const;
    void set(const std::string& name, const Value& value);
    void set(std::pair<std::string, const Value&> var_and_value);
private:
    std::unordered_map<std::string, Value> variables;
};