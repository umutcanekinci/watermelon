#pragma once
#include <string>
#include <variant>
#include <stdexcept>
#include <iostream>

class Value {
public:
    using VariantType = std::variant<int, float, bool, std::string>;
    VariantType data;

    Value();
    Value(int v);
    Value(float v);
    Value(bool v);
    Value(const std::string &v);

    bool is_null() const;

    bool is_int() const;
    bool is_float() const;
    bool is_bool() const;
    bool is_string() const;

    int as_int() const;
    float as_float() const;
    bool as_bool() const;
    std::string as_string() const;
    std::string to_string() const;
};