#include <iostream>
#include "stack.h"

using namespace std;

/*
* How can we make a generic class Stack for compatible with both classes and primitives?
* Because we can't use pointers with primitive types
* Wrappers?
 "" is a pointer?
*/

template <typename T>
class Stack {
    T **array;
    int top, size;
public:
    Stack() {
        size = 100;
        array = new T*[size];
        top = -1;
    }

    void push(T* value);
    T* get(), * pop();
    bool is_empty();
    bool is_full();
    void display();
    void pop_all_to_string(string *s);
    T* pop_to_string(string *s);
    int length() {
        return top + 1;
    }
};

template <typename T>
void Stack<T>::push(T* value) {
    array[++top] = value;
}

template <typename T>
T* Stack<T>::pop() {
    return is_empty() ? nullptr : array[top--];
}

template <typename T>
bool Stack<T>::is_empty() {
    return top == -1;
}

template <typename T>
bool Stack<T>::is_full() {
    return top == size-1;
}

template <typename T>
T* Stack<T>::get() {
    return is_empty() ? nullptr : array[top];
}

template <typename T>
void Stack<T>::display() {
    for(int i=0; i<=top; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Stack<T>::pop_all_to_string(string *s) {
    while (!is_empty())
        *s += pop()->get_value();
}

template <typename T>
T* Stack<T>::pop_to_string(string *s) {
    if (is_empty())
        return nullptr;
    T* value = pop();
    *s += value->get_value();
    return value;
}