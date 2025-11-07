#pragma once
#include <string>
#include <variant>
#include <stdexcept>
#include <iostream>

class Value {
public:
    enum class Kind { Int, Float, Bool, String, Reference };
private:
    Kind kind;
    using VariantType = std::variant<int, float, bool, std::string>;
    VariantType data;
    std::string reference_name;

public:
    Value();
    Value(int v);
    Value(float v);
    Value(bool v);
    Value(const std::string &v);

    static Value make_reference(const std::string &var_name);

    bool is_null() const;

    bool is_int() const;
    bool is_float() const;
    bool is_bool() const;
    bool is_string() const;
    bool is_reference() const;

    int as_int() const;
    float as_float() const;
    bool as_bool() const;
    std::string as_string() const;
    const std::string & as_variable_name() const;

    std::string to_string() const;
};