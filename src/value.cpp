#include "value.h"

using namespace std;

Value::Value() : data(0) {}
Value::Value(int v) : data(v) {}
Value::Value(float v) : data(v) {}
Value::Value(bool v) : data(v) {}
Value::Value(const string &v) : data(v) {}

bool Value::is_null() const {
    return std::holds_alternative<int>(data) && as_int() == 0;
}

bool Value::is_int() const { return std::holds_alternative<int>(data); }
bool Value::is_float() const { return std::holds_alternative<float>(data); }
bool Value::is_bool() const { return std::holds_alternative<bool>(data); }
bool Value::is_string() const { return std::holds_alternative<std::string>(data); }

int Value::as_int() const { return std::get<int>(data); }
float Value::as_float() const { return std::get<float>(data); }
bool Value::as_bool() const { return std::get<bool>(data); }
string Value::as_string() const { return std::get<std::string>(data); }

string Value::to_string() const {
    if (is_int()) return std::to_string(as_int());
    if (is_float()) return std::to_string(as_float());
    if (is_bool()) return as_bool() ? "true" : "false";
    return as_string();
}