#pragma once
#include <string>
#include <vector>
using namespace std;

class Token;

class ScriptLine {
private:
    string line;
    vector<Token> tokens;
public:
    ScriptLine(const string& line);
    string get_line() const;
    vector<Token> tokenize() const;
    bool is_comment() const;
    bool is_empty() const;
};
