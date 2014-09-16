#include "JEB/Unicode/UnicodePredicates.hpp"

#include <JEBTest/JEBTest.hpp>

//using namespace JEB::String;

static void test_Whitespace()
{
    JT_ASSERT(JEB::Unicode::isWhitespace(' '));
    JT_ASSERT(!JEB::Unicode::isWhitespace('A'));
}

JT_TEST(test_Whitespace);
