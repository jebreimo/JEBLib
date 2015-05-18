#include "JEBMath/Geometry/Plane3.hpp"
#include <cmath>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Units()
{
    Plane3<double> plane1(vector3(1, 1, 1), vector3(1, 1, 1));
    Vector<double, 3> u1, u2;
    JT_ASSERT(plane1.getUnitVectors(u1, u2));

    JT_ASSERT(areEquivalent(
            u1,
            vector3(-1 / std::sqrt(2.0),  1 / std::sqrt(2.0), 0.0),
            1e-10));
    JT_ASSERT(areEquivalent(
            u2,
            vector3(-1 / std::sqrt(6.0),
                    -1 / std::sqrt(6.0),
                    std::sqrt(2.0 / 3.0)),
            1e-10));
}

JT_SUBTEST("Geometry", test_Units);
