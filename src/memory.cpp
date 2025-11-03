#include "memory.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

Memory::Memory() {}

int Memory::get(const string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw runtime_error("Variable " + name + " not found");
}

void Memory::set(const string& name, int value) {
    cout << "[MEMORY] Setting variable " << name << " with value " << value << endl;
    variables[name] = value;
}

void Memory::set(pair<string, int> var_and_value) {
    set(var_and_value.first, var_and_value.second);
}