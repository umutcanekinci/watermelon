#include "value.h"

using namespace std;

Value::Value()                : kind(Kind::Int)   , data(0) {}
Value::Value(int v)           : kind(Kind::Int)   , data(v) {}
Value::Value(float v)         : kind(Kind::Float) , data(v) {}
Value::Value(bool v)          : kind(Kind::Bool)  , data(v) {}
Value::Value(const string &v) : kind(Kind::String), data(v) {}

Value Value::make_reference(const string &var_name) {
    Value v;
    v.kind = Kind::Reference;
    v.reference_name = var_name;
    return v;
}

bool Value::is_null() const {
    return std::holds_alternative<int>(data) && as_int() == 0;
}

// Type checkers
bool Value::is_int() const {
    return kind == Kind::Int;
}
bool Value::is_float() const {
    return kind == Kind::Float;
}
bool Value::is_bool() const {
    return kind == Kind::Bool; 
}
bool Value::is_string() const {
    return kind == Kind::String;
}
bool Value::is_reference() const {
    return kind == Kind::Reference;
}

// Accessors
int Value::as_int() const {
    return std::get<int>(data);
}
float Value::as_float() const {
    return std::get<float>(data);
}
bool Value::as_bool() const {
    return std::get<bool>(data);
}
string Value::as_string() const {
    return std::get<std::string>(data);
}
const string & Value::as_variable_name() const {
    if (kind != Kind::Reference)
        throw runtime_error("Value is not a reference");
    return reference_name;
}

string Value::to_string() const {
    if (is_int()) return std::to_string(as_int());
    if (is_float()) return std::to_string(as_float());
    if (is_bool()) return as_bool() ? "true" : "false";
    if (is_string()) return as_string();
    return reference_name;
}