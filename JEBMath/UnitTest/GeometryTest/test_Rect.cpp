#include "JEBMath/Geometry/Rect.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;
using namespace JEBMath::Dim2;

static void test_center()
{
    auto rect = Rect<int>{point2(0, 0), vector2(20, 40)};
    JT_EQUAL(rect.center(), point2(10, 20));
    rect.setCenter(point2(0, 0));
    JT_EQUAL(rect.center(), point2(0, 0));
    JT_EQUAL(rect.point(0), point2(-10, -20));
}

JT_SUBTEST("Geometry", test_center);
