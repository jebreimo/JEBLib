#include "JEBMath/Geometry/Rect.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_center()
{
    auto rect = makeRect(vector2(0, 0), vector2(20, 40));
    JT_EQUAL(rect.getCenter(), vector2(10, 20));
    rect.setCenter(vector2(0, 0));
    JT_EQUAL(rect.getCenter(), vector2(0, 0));
    JT_EQUAL(rect.getPoint(0), vector2(-10, -20));
}

JT_SUBTEST("Geometry", test_center);
