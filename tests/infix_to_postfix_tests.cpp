#ifndef INFIX_TO_POSTFIX_TEST_CPP
#define INFIX_TO_POSTFIX_TEST_CPP

#include "infix_to_postfix.h"
#include "tests.cpp"

void test_infix_to_postfix() {
    test_function("a+b"                    , "ab+", &InfixToPostfix);
    test_function("a+b*c"                  , "abc*+", &InfixToPostfix);
    test_function("a+b*c-d/e"              , "abc*+de/-", &InfixToPostfix);
    test_function("(a+b)*c"                , "ab+c*", &InfixToPostfix);
    test_function("a+b*(c*d-e)"           , "abcd*e-*+", &InfixToPostfix);
    test_function("a+b*(c-d/e)"           , "abcde/-*+", &InfixToPostfix);
    test_function("((a+b)*c)-d"           , "ab+c*d-", &InfixToPostfix);
    test_function("a+(b*c-(d/e^f)*g)*h"   , "abc*def^/g*-h*+", &InfixToPostfix);
}

#endif