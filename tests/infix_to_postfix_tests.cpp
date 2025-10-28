#ifndef INFIX_TO_POSTFIX_TEST_CPP
#define INFIX_TO_POSTFIX_TEST_CPP

#include "../src/infix_to_postfix.cpp"
#include "tests.cpp"

void test_infix_to_postfix() {
    test("a+b"                    , "ab+", &InfixToPostfix);
    test("a+b*c"                  , "abc*+", &InfixToPostfix);
    test("a+b*c-d/e"              , "abc*+de/-", &InfixToPostfix);
    test("(a+b)*c"                , "(ab+c)*", &InfixToPostfix);
    test("a+b*(c^d-e)^(f+g*h)-i"  , "ab+cde^-fgh*+i-", &InfixToPostfix);
    test("((a+b)*c-(d/e))^f+g*h-i", "((ab+c)*de/-)^fgh*-i", &InfixToPostfix);

}

#endif