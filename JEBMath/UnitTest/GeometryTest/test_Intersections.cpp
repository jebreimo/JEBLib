#include "JEBMath/Geometry/Distance.hpp"
#include "JEBMath/Geometry/Intersections.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;
using namespace JEBMath::Dim2;

static void test_ContainsPoint()
{
    LineSegmentD ls(pointD(0.0, 0.0), pointD(4.0, 6.0));
    JT_ASSERT(containsPoint(ls, pointD(0, 0), 1e-9));
    JT_ASSERT(containsPoint(ls, pointD(4, 6), 1e-9));
    JT_ASSERT(containsPoint(ls, pointD(-1e-10, 0.0), 1e-9));
    JT_ASSERT(containsPoint(ls, pointD(4 + 1e-10, 6.0), 1e-9));
    JT_ASSERT(!containsPoint(ls, pointD(-1e-8, 0.0), 1e-9));
    JT_ASSERT(!containsPoint(ls, pointD(4 + 1e-8, 6.0), 1e-9));
    JT_ASSERT(containsPoint(ls, pointD(1.4 / 2.1, 1), 1e-9));
}

static void test_Distance()
{
    LineD l(point2(-3.0, 2.0), vector2(6.0, 0.0));
    PointD p = point2(0.0, 0.0);
    JT_EQUIVALENT(distance(l, p), -2, 1e-10);
}

static void test_Intersects()
{
    LineSegmentD a(point2(-5.0,  3.0), point2( 7.0, -3.0));
    LineSegmentD b(point2(-1.0, -2.0), point2(11.0,  4.0));
    JT_ASSERT(intersects(a, b, 0));
    JT_ASSERT(intersects(a, reverse(b), 0));
    JT_ASSERT(intersects(reverse(a), b, 0));
}

static void test_Overlap()
{
    LineSegmentD a(point2(0.0, 0.0), point2(5.0, 5.0));
    LineSegmentD b(point2(6.0, 6.0), point2(2.0, 2.0));
    std::pair<double, double> offsA, offsB;
    JT_ASSERT(overlap(offsA, offsB, a, b, 1e-9));
    JT_EQUAL(offsA.first, 1.0);
    JT_EQUAL(offsA.second, 0.4);
    JT_EQUAL(offsB.first, 0.25);
    JT_EQUAL(offsB.second, 1.0);
}

static void test_AreTangentialAtPoint()
{
    PointD p[] = {
        pointD(0, 0),
        pointD(-1, 3),
        pointD(3, 1),
        pointD(1, -3),
        pointD(-3, -1),
        pointD(-1.9, 5.7),
        pointD(5.7, 1.9)
    };

    JT_ASSERT(areTangentialAtPoint(p[0], p[1], p[2], p[3], p[4]));
    JT_ASSERT(areTangentialAtPoint(p[0], p[1], p[2], p[4], p[3]));
    JT_ASSERT(areTangentialAtPoint(p[0], p[2], p[1], p[3], p[4]));
    JT_ASSERT(areTangentialAtPoint(p[0], p[2], p[1], p[4], p[3]));
    JT_ASSERT(!areTangentialAtPoint(p[0], p[1], p[3], p[2], p[4]));
    JT_ASSERT(!areTangentialAtPoint(p[0], p[1], p[3], p[4], p[2]));
    JT_ASSERT(!areTangentialAtPoint(p[0], p[3], p[1], p[2], p[4]));
    JT_ASSERT(!areTangentialAtPoint(p[0], p[3], p[1], p[4], p[2]));
    JT_ASSERT(areTangentialAtPoint(p[0], p[1], p[2], p[3], p[5], 1e-9));
}

JT_SUBTEST("Geometry",
           test_ContainsPoint,
           test_Distance,
           test_Intersects,
           test_Overlap,
           test_AreTangentialAtPoint);
