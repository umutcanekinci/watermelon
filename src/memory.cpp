#include "memory.h"
#include <iostream>
#include <stdexcept>
#include <string>

Memory::Memory() {}

int Memory::get(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Variable " + name + " not found");
}

void Memory::set(const std::string& name, int value) {
    std::cout << "[MEMORY] Setting variable " << name << " with value " << value << std::endl;
    variables[name] = value;
}
