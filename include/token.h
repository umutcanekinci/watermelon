#pragma once
#include <string>
#include <vector>
using namespace std;

class Token {
public:
    enum Type {
        NUMBER,
        OPERATOR,
        VARIABLE,
        PARENTHESIS
    };

    Token(Type type, const string& value);

    Type get_type() const;
    string get_value() const;
    bool empty() const;
    static Type determine_type(const string& token);
private:
    Type type;
    string value;
};