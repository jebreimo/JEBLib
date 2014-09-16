#include "JEBMath/Geometry/CubicHermiteSpline.hpp"

#include "JEBMath/Geometry/Point.hpp"
#include "JEBMath/Geometry/Vector.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Dim2()
{
    typedef Point<double, 2> P;
    typedef Vector<double, 2> V;
    typedef CubicHermiteSpline<P, V> CHS;
    P p1 = point2<double>(1, 1);
    V v1 = vector2<double>(1, 1);
    P p2 = point2<double>(3, 1);
    V v2 = vector2<double>(1, -1);
    CHS spline(p1, v1, p2, v2);
    JT_EQUAL(spline.start(), p1);
    JT_EQUAL(spline.startTangent(), v1);
    JT_ASSERT(equivalent(spline.end(), p2, 1e-12));
    JT_ASSERT(equivalent(spline.endTangent(), v2, 1e-12));
    P mid = spline.pointAt(0.5);
    JT_EQUIVALENT(x(mid), 2, 1e-12);
}

JT_SUBTEST("Geometry", test_Dim2);
