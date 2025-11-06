#pragma once
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include "value.h"

class Memory;

// Simple helpers to keep operator implementations small and readable.
static inline Value add_op(Value a, Value b, Memory *mem) {
    // String concatenation wins if either side is a string.
    if (a.is_string() || b.is_string())
        return Value(a.to_string() + b.to_string());
    if (a.is_float() || b.is_float())
        return Value(a.as_float() + b.as_float());
    return Value(a.as_int() + b.as_int());
}

static inline Value sub_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() - b.as_float());
    return Value(a.as_int() - b.as_int());
}

static inline Value mul_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() * b.as_float());
    return Value(a.as_int() * b.as_int());
}

static inline bool is_zero(const Value &v) {
    return (v.is_int() && v.as_int() == 0) || (v.is_float() && v.as_float() == 0.0);
}

static inline Value div_op(Value a, Value b, Memory *mem) {
    if (is_zero(b))
        throw std::runtime_error("Division by zero");
    if (a.is_float() || b.is_float())
        return Value(a.as_float() / b.as_float());
    return Value(a.as_int() / b.as_int());
}

static inline Value eq_op(Value a, Value b, Memory *mem) {
    return Value(a.to_string() == b.to_string());
}

static inline Value and_op(Value a, Value b, Memory *mem) {
    return Value(a.as_bool() && b.as_bool());
}

static inline Value or_op(Value a, Value b, Memory *mem) {
    return Value(a.as_bool() || b.as_bool());
}

static inline Value assign_op(Value a, Value b, Memory *mem) {
    if (!a.is_string())
        throw std::runtime_error("Left side of assignment must be a variable name");

    mem->set(a.as_string(), b);
    return b;
}

struct OperatorInfo {
    int precedence;
    bool rightAssociative;
    std::function<Value(Value, Value, Memory *)> func;
};

static const std::unordered_map<std::string, OperatorInfo> OPERATOR_TABLE = {
    {"+",  { 1, false, add_op }},
    {"-",  { 1, false, sub_op }},
    {"*",  { 2, false, mul_op }},
    {"/",  { 2, false, div_op }},
    {"==", { 0, false, eq_op  }},
    {"&&", {-1, false, and_op }},
    {"||", {-2, false, or_op  }},
    {"=", { 0, true, assign_op }}
};