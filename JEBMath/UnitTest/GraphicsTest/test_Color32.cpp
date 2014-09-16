#include "JEBMath/Graphics/Color32.hpp"

#include <iostream>
#include <JEBTest/JEBTest.hpp>

using namespace JEB;

static void TestColor32(const Color32& c,
                        uint8_t a,
                        uint8_t r,
                        uint8_t g,
                        uint8_t b)
{
    JT_EQUAL(c.alpha(), a);
    JT_EQUAL(c.red(), r);
    JT_EQUAL(c.green(), g);
    JT_EQUAL(c.blue(), b);
}

void test_color()
{
    Color32 a(100, 50, 200);
    Color32 b(200, 250, 0);

    TestColor32(a, 255, 100, 50, 200);
    Color32 c = interpolateRgb(a, b, 0.5);
    TestColor32(c, 255, 150, 150, 100);
}

JT_SUBTEST("Graphics", test_color);
