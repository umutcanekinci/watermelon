#pragma once
#include <exception>
#include <string>
#include "location.h"

class Error : public std::exception {
private:
    std::string prefix;
    std::string message;
    Location location;
public:
    Error(const std::string& message, const Location& location) {
        this->prefix = "[Error]";
        this->message = message;
        this->location = location;
    }

    Error(const std::string& prefix, const std::string& message, const Location& location) {
        this->prefix = prefix;
        this->message = message;
        this->location = location;
    }
    
    const char* what() const noexcept override {
        return message.c_str();
    }

    Location get_location() const {
        return location;
    }
};