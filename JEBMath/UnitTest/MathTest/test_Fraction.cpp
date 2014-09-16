#include "JEBMath/Math/Fraction.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

typedef Fraction<int> F;

void test_Construction()
{
    JT_EQUAL(F(0, 1), F());
    JT_EQUAL(F(1, 1), F(1));
    JT_EQUAL(F(9, 63), F(1, 7));
    JT_EQUAL(F(21, -49), F(-3, 7));
}

void test_Math()
{
    F a(1, 3);
    F b(1, 6);
    JT_EQUAL(a + b, F(1, 2));
    JT_EQUAL(b + a, F(1, 2));
    JT_EQUAL(-a + -b, F(-1, 2));
    JT_EQUAL(a - b, F(1, 6));
    JT_EQUAL(b - a, F(-1, 6));
    JT_EQUAL(a * b, F(1, 18));
    JT_EQUAL(-a * b, F(-1, 18));
    JT_EQUAL(a / b, F(2, 1));
    JT_EQUAL(a / -b, F(-2, 1));
}

JT_SUBTEST("Math", test_Construction, test_Math);
