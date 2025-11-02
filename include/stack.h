#pragma once

#include <string>

using namespace std;

template <typename T>
class Stack {
private:
    T **array;
    int top;
    int size;
public:
    Stack();
    void push(T* value);
    T* get(), * pop();
    bool is_empty();
    bool is_full();
    void display();
    void pop_all_to_string(string *s);
    T* pop_to_string(string *s);
};