#include "../Integers.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEB::Integers;

void test_binary()
{
    int a = -1;
    JT_EQUAL(binary(a), "11111111111111111111111111111111");
    a = (1 << 31) + (0xF << 12);
    JT_EQUAL(binary(a), "10000000000000001111000000000000");
}

void test_hexadecimal()
{
    int a = -1;
    JT_EQUAL(hexadecimal(a), "FFFFFFFF");
    a = (1 << 31) + (0xF << 12);
    JT_EQUAL(hexadecimal(a), "8000F000");
}

JT_TEST(test_binary, test_hexadecimal);
