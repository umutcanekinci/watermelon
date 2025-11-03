#pragma once
#include <iostream>
#include <string>

class Operator;

template <typename T>
class Stack {
private:
    T *array;
    int top;
    int size;
public:
    Stack();
    void push(const T &value);
    T get();
    T pop();
    bool is_empty();
    bool is_full();
    int length();
    void display();
    void pop_all_to_other(Stack<T> *other);
    T pop_to_other(Stack<T> *other);
};

/*
* How can we make a generic class Stack for compatible with both classes and primitives?
* Because we can't use pointers with primitive types
* Wrappers?
 "" is a pointer?
*/

template <typename T>
Stack<T>::Stack() {
    size = 100;
    array = new T[size];
    top = -1;
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (is_full())
        return;
    array[++top] = value;
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty())
        throw std::runtime_error("Stack is empty");
    return array[top--];
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
T Stack<T>::get() {
    if (is_empty())
        throw std::runtime_error("Stack is empty");
    return array[top];
}

template <typename T>
int Stack<T>::length() {
    return top + 1;
}

template <typename T>
void Stack<T>::display() {
    for(int i=0; i<=top; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Stack<T>::pop_all_to_other(Stack<T> *other) {
    while (!is_empty())
        other->push(pop());
}

template <typename T>
T Stack<T>::pop_to_other(Stack<T> *other) {
    T value = pop();
    other->push(value);
    return value;
}