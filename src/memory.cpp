#include "memory.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "value.h"
using namespace std;

Memory::Memory() {}

Value Memory::get(const string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return Value(); // Return null Value if not found
}

void Memory::set(const string& name, const Value& value) {
    cout << "[MEMORY] "<< name << " = " << value.to_string() << endl;
    variables[name] = value;
}

void Memory::set(pair<string, const Value&> var_and_value) {
    set(var_and_value.first, var_and_value.second);
}