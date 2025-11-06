#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>
#include "value.h"
#include "memory.h"

struct OperatorInfo {
    int precedence;
    bool rightAssociative;
    std::function<Value(Value, Value, Memory *)> func;
};

struct OperatorTable {
    static const std::unordered_map<std::string, OperatorInfo> TABLE;

    static const OperatorInfo* get(const std::string& op) {
        auto it = TABLE.find(op);

        if (it == TABLE.end())
            throw std::runtime_error("Unknown operator: " + op);

        return &it->second;
    }
};
