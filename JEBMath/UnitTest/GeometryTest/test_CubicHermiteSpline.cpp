#include "JEBMath/Geometry/CubicHermiteSpline.hpp"

// #include "JEBMath/Geometry/Point.hpp"
#include "JEBMath/Geometry/Vector.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Dim2()
{
    // typedef Point<double, 2> P;
    // typedef CubicHermiteSpline<2> CHS;
    auto p1 = vector2(1.0, 1.0);
    auto v1 = vector2(1.0, 1.0);
    auto p2 = vector2(3.0, 1.0);
    auto v2 = vector2(1.0, -1.0);
    CubicHermiteSpline<2> spline(p1, v1, p2, v2);
    JT_EQUAL(spline.getStart(), p1);
    JT_EQUAL(spline.getStartTangent(), v1);
    JT_ASSERT(areEquivalent(spline.getEnd(), p2, 1e-12));
    JT_ASSERT(areEquivalent(spline.getEndTangent(), v2, 1e-12));
    JT_EQUIVALENT(getX(spline.getPointAt(0.5)), 2, 1e-12);
}

JT_SUBTEST("Geometry", test_Dim2);
