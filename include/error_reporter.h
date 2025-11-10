#pragma once
#include <string>
#include <vector>
#include "location.h"

enum class ErrorType {
    Syntax,
    Runtime,
    Validation
};

/*
* Diagnostic class is for compile time errors.
* They will store in a vector in ErrorReporter.
* And show all at once after compilation. Before runtime.
* Runtime errors will be thrown as exceptions.
*/
struct Diagnostic {
    ErrorType type;
    std::string message;
    Location location;

    std::string to_string() const {
        std::string prefix;
        switch (type) {
            case ErrorType::Syntax: prefix = "SyntaxError"; break;
            case ErrorType::Runtime: prefix = "RuntimeError"; break;
            case ErrorType::Validation: prefix = "ValidationError"; break;
        }
        return prefix + " (" + location.to_string() + "): " + "\n" + message;
    }
};

class ErrorReporter {
    private:
        std::vector<Diagnostic> diagnostics;
    public:
        void log(ErrorType type, const std::string& message, const Location& location);
        bool has_errors() const;
        void display_errors() const;
        void clear_errors();
};