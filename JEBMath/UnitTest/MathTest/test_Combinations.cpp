#include "JEBMath/Math/Combinations.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Index()
{
    JT_EQUAL(Combinations::index(0), 0);
    JT_EQUAL(Combinations::index(1), 1);
    JT_EQUAL(Combinations::index(0x10), 5);
    JT_EQUAL(Combinations::index(0x80000000u), 32);
    JT_EQUAL(Combinations::index(3), 33);
    JT_EQUAL(Combinations::index(5), 34);
    JT_EQUAL(Combinations::index(0x80000001u), 63);
    JT_EQUAL(Combinations::index(0x80000002u), 93);
    JT_EQUAL(Combinations::index(3, 6), 7);
    JT_EQUAL(Combinations::index(0x30, 6), 21);
    JT_EQUAL(Combinations::index(7, 6), 22);
}

static void test_LocalIndex()
{
    JT_EQUAL(Combinations::localIndex(0x7, 7), 0);
    JT_EQUAL(Combinations::localIndex(0xB, 7), 1);
    JT_EQUAL(Combinations::localIndex(0xE, 7), 15);
}

JT_SUBTEST("Math", test_Index, test_LocalIndex);
