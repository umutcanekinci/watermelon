#include "script_line.h"
#include "token.h"
#include <string>
using namespace std;

/* Parse line to the operators, numbers, and variables
a=5 -> ["a", "=", "5"]
a=a+b -> ["a", "=", "a", "+", "b"]
var = var1 + var2 * 10 -> ["var", "=", "var1", "+", "var2", "*", "10"]
*/
vector<Token> ScriptLine::tokenize() const {
    string current_token = "";
    Token::Type type;
    for (char ch : line) {
        type = Token::determine_type(current_token);
        Token token(type, current_token);
        if (token.get_type() == Token::OPERATOR) {
            if (current_token.empty())
                continue;
            
            tokens.emplace_back(type, current_token);
            current_token = "";
            continue;
        }
        current_token += ch;
    }
    if (!current_token.empty())
        tokens.push_back(Token(Token::determine_type(current_token), current_token));

    return tokens;
}