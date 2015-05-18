#include "JEBMath/Geometry/Distance.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_PointPoint()
{
    JT_EQUAL(getDistance(vector2(1, 2), vector2(1.0, 2.0)), 0);
    JT_EQUIVALENT(getDistance(vector2(1, 2), vector2(7.0, 12.0)),
                  11.661903789690601, 1e-12);
}

JT_SUBTEST("Geometry",
           test_PointPoint);
