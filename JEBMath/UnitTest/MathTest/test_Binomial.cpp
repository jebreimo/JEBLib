#include "JEBMath/Math/Binomial.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Values()
{
    JT_EQUAL(binomial(0, 0), 0);
    JT_EQUAL(binomial(1, 0), 1);
    JT_EQUAL(binomial(10, 11), 0);
    JT_EQUAL(binomial(10, -1), 0);
    JT_EQUAL(binomial(10, 0), 1);
    JT_EQUAL(binomial(6, 3), 20);
    JT_EQUAL(binomial(7, 3), 35);
    JT_EQUAL(binomial(7, 2), binomial(7, 5));
}

JT_SUBTEST("Math", test_Values);
