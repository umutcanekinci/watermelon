#ifndef STACK_TEST_CPP
#define STACK_TEST_CPP

#include "../src/stack.cpp"

void test_stack() {
    Stack<int> *s = new Stack<int>();
    // s->push(10);
    // s->push(20);
    // s->pop();
    // s->push(30);
    s->display();
}

#endif