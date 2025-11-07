#pragma once
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include "value.h"
#include "operator_table.h"
#include "memory.h"

static inline bool is_zero(const Value &v) {
    return (v.is_int() && v.as_int() == 0) || (v.is_float() && v.as_float() == 0.0);
}


static inline Value mul_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() * b.as_float());
    return Value(a.as_int() * b.as_int());
}

static inline Value div_op(Value a, Value b, Memory *mem) {
    if (is_zero(b))
        throw std::runtime_error("Division by zero");
    if (a.is_float() || b.is_float())
        return Value(a.as_float() / b.as_float());
    return Value(a.as_int() / b.as_int());
}

static inline Value mod_op(Value a, Value b, Memory *mem) {
    if (is_zero(b))
        throw std::runtime_error("Modulo by zero");
    return Value(a.as_int() % b.as_int());
}

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

static inline Value less_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() < b.as_float());
    return Value(a.as_int() < b.as_int());
}

static inline Value less_equal_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() <= b.as_float());
    return Value(a.as_int() <= b.as_int());
}

static inline Value greater_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() > b.as_float());
    return Value(a.as_int() > b.as_int());
}

static inline Value greater_equal_op(Value a, Value b, Memory *mem) {
    if (a.is_float() || b.is_float())
        return Value(a.as_float() >= b.as_float());
    return Value(a.as_int() >= b.as_int());
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

static inline Value assign_op(Value a, Value b, Memory* memory) {
    if (!a.is_reference())
        throw std::runtime_error("Left-hand side of assignment must be a variable name");

    // resolve b if it is reference (opsiyonel: burada lambda'ya bırakabilirsin)
    if (b.is_reference()) {
        auto tmp = memory->get(b.as_variable_name());
        if (tmp.is_null()) throw std::runtime_error("Undefined variable: " + b.as_variable_name());
        b = tmp;
    }

    memory->set(a.as_variable_name(), b);
    return b; // assignment expression returns RHS value
}


const std::unordered_map<std::string, OperatorInfo> OperatorTable::TABLE = {
    // Postfix
    {"(", { 13,  false, nullptr }},
    {")", { 13,  false, nullptr }},
    // {"[]", { 13,  false, nullptr }},
    // {".",  { 13,  false, nullptr }},
    // {"++", { 12,  false, nullptr }},
    // {"--", { 12,  false, nullptr }},
    
    // Unary
    // {"+",  { 12,  true, nullptr }},
    // {"-",  { 12,  true, nullptr }},
    // {"!",  { 12,  true, nullptr }},
    // {"~",  { 12,  true, nullptr }},
    // {"++", { 12,  true, nullptr }},
    // {"--", { 12,  true, nullptr }},

    // Multiplicative
    {"*",  { 12,  false, mul_op }},
    {"/",  { 12,  false, div_op }},
    {"%",  { 12,  false, mod_op }},

    // Additive
    {"+",  { 11,  false, add_op }},
    {"-",  { 11,  false, sub_op }},

    // Shift
    // {"<<", { 10,  false, nullptr }},
    // {">>", { 10,  false, nullptr }},

    // Relational
    {"<",  { 9,  false, less_op }},
    {"<=", { 9,  false, less_equal_op }},
    {">",  { 9,  false, greater_op }},
    {">=", { 9,  false, greater_equal_op }},

    // Equality
    {"==", { 8,  false, eq_op }},
    {"!=", { 8,  false, nullptr }},

    // Bitwise
    // {"&",  { 7,  false, nullptr }},
    // {"^",  { 6,  false, nullptr }},
    // {"|",  { 5,  false, nullptr }},
    // & ^ | not implemented yet

    // Logical
    {"&&", { 4,  false, and_op }},
    {"||", { 3,  false, or_op }},
    
    // Conditional
    {"?",  { 2,  true, nullptr }},
    {":",  { 2,  true, nullptr }},

    // Assignment
    {"=",  { 1,  true,  assign_op }},
    // {"+=", { 1,  true, nullptr }},
    // {"-=", { 1,  true, nullptr }},
    // {"*=", { 1,  true, nullptr }},
    // {"/=", { 1,  true, nullptr }},
    // {"%=", { 1,  true, nullptr }},
    // {"<<=",{ 1,  true, nullptr }},
    // {">>=",{ 1,  true, nullptr }},
    // {"&=", { 1,  true, nullptr }},
    // {"^=", { 1,  true, nullptr }},
    // {"|=", { 1,  true, nullptr }},

    // Comma
    // {",",  { 0, false, nullptr }}
};