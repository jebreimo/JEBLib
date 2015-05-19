#include "JEBMath/Geometry/SortPoints.hpp"
#include "JEBMath/Geometry/LineSegment.hpp"

// #include "JEBMath/Geometry/Types.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

void assertLess(const DirectionComparer<double>& cmp,
                const Vector<double, 2>& p, const Vector<double, 2>& q)
{
    JT_ASSERT_MSG(cmp(p, q), p << " not less than " << q);
    JT_ASSERT_MSG(!cmp(q, p), q << " not less than " << p);
}

void test_SortClockwise()
{
    LineSegment<double, 3> lines[] = {
        makeLineSegment(vector3(2.0, 2.0, 0.0), vector3(0.0, 0.0, 3.0)),
        makeLineSegment(vector3(2.0, 2.0, 0.0), vector3(4.0, 4.0, 1.0)),
        makeLineSegment(vector3(2.0, 2.0, 0.0), vector3(0.0, 4.0, 5.0)),
        makeLineSegment(vector3(2.0, 2.0, 0.0), vector3(4.0, 0.0, 1.0))
    };
    sortClockwise(std::begin(lines), std::end(lines), vector2(2.0, 2.0),
                  [](const LineSegment<double, 3>& l)
                  {return vector2(getX(l.getEnd()), getY(l.getEnd()));});
    JT_EQUAL(lines[0].getEnd(), vector3(4.0, 4.0, 1.0));
    JT_EQUAL(lines[1].getEnd(), vector3(0.0, 4.0, 5.0));
    JT_EQUAL(lines[2].getEnd(), vector3(0.0, 0.0, 3.0));
    JT_EQUAL(lines[3].getEnd(), vector3(4.0, 0.0, 1.0));
}

void test_CompareXYDirections()
{
    DirectionComparer<double> cmp(vector2(5.0, 3.0));
    Vector<double, 2> p[] = {
        vector2(8.0, 3.0),
        vector2(7.0, 3.0),
        vector2(5.0, 3.0),
        vector2(2.0, 3.0),
        vector2(1.0, 3.0),
        vector2(7.0, 4.0),
    };
    assertLess(cmp, p[0], p[1]);
    assertLess(cmp, p[0], p[2]);
    assertLess(cmp, p[1], p[2]);
    assertLess(cmp, p[0], p[3]);
    assertLess(cmp, p[1], p[3]);
    assertLess(cmp, p[3], p[2]);
    assertLess(cmp, p[4], p[3]);
    assertLess(cmp, p[1], p[5]);
}

void test_SortBug()
{
    Vector<double, 2> p[] = {
        vector2(5.0, 0.0),
        vector2(0.0, 5.0),
        vector2(-5.0, 0.0),
        vector2(0.0, -5.0),
        vector2(4.0, 3.0),
        vector2(-4.0, 3.0),
        vector2(-4.0, -3.0),
        vector2(4.0, -3.0),
        vector2(3.0, 4.0),
        vector2(-3.0, 4.0),
        vector2(-3.0, -4.0),
        vector2(3.0, -4.0),
    };
    DirectionComparer<double> cmp(vector2(0.0, 0.0));
    assertLess(cmp, p[0], p[4]);
    assertLess(cmp, p[4], p[8]);
    assertLess(cmp, p[8], p[1]);
    assertLess(cmp, p[1], p[9]);
    assertLess(cmp, p[9], p[5]);
    assertLess(cmp, p[5], p[2]);
    assertLess(cmp, p[2], p[6]);
    assertLess(cmp, p[6], p[10]);
    assertLess(cmp, p[10], p[3]);
    assertLess(cmp, p[3], p[11]);
    assertLess(cmp, p[11], p[7]);

    assertLess(cmp, p[0], p[7]);

    for (int i = 1; i < sizeof(p) / sizeof(*p); ++i)
      assertLess(cmp, p[0], p[i]);
}

void test_SortClockwiseXY()
{
    Vector<double, 2> points[] = {
        vector2(5.0, 0.0),
        vector2(0.0, 5.0),
        vector2(-5.0, 0.0),
        vector2(0.0, -5.0),
        vector2(4.0, 3.0),
        vector2(-4.0, 3.0),
        vector2(-4.0, -3.0),
        vector2(4.0, -3.0),
        vector2(3.0, 4.0),
        vector2(-3.0, 4.0),
        vector2(-3.0, -4.0),
        vector2(3.0, -4.0),
    };
    std::vector<Vector<double, 2>> vec(std::begin(points), std::end(points));
    sortClockwise(vec, vector2(0.0, 0.0));
    JT_EQUAL(vec[0], points[0]);
    JT_EQUAL(vec[1], points[4]);
    JT_EQUAL(vec[2], points[8]);
    JT_EQUAL(vec[3], points[1]);
    JT_EQUAL(vec[4], points[9]);
    JT_EQUAL(vec[5], points[5]);
    JT_EQUAL(vec[6], points[2]);
    JT_EQUAL(vec[7], points[6]);
    JT_EQUAL(vec[8], points[10]);
    JT_EQUAL(vec[9], points[3]);
    JT_EQUAL(vec[10], points[11]);
    JT_EQUAL(vec[11], points[7]);
}

void test_SortXY()
{
    Vector<double, 2> points[] = {
        vector2( 0.0,  0.0), //  0
        vector2(-2.0,  0.0), //  1
        vector2( 2.0,  0.0), //  2
        vector2(-2.0, -1.0), //  3
        vector2(-2.0,  1.0), //  4
        vector2( 2.0, -1.0), //  5
        vector2( 2.0,  1.0), //  6
        vector2(-3.0, -1.0), //  7
        vector2(-1.0, -1.0), //  8
        vector2(-3.0,  1.0), //  9
        vector2(-1.0,  1.0), // 10
        vector2( 1.0, -1.0), // 11
        vector2( 3.0, -1.0), // 12
        vector2( 1.0,  1.0), // 13
        vector2( 3.0,  1.0)  // 14
    };
    std::vector<Vector<double, 2>> vec(std::begin(points), std::end(points));
    sortPointsXY(vec.begin(), vec.end());
    JT_EQUAL(vec[7], points[0]);
    JT_EQUAL(vec[3], points[1]);
    JT_EQUAL(vec[11], points[2]);
    JT_EQUAL(vec[1], points[3]);
    JT_EQUAL(vec[5], points[4]);
    JT_EQUAL(vec[9], points[5]);
    JT_EQUAL(vec[13], points[6]);
    JT_EQUAL(vec[0], points[7]);
    JT_EQUAL(vec[2], points[8]);
    JT_EQUAL(vec[4], points[9]);
    JT_EQUAL(vec[6], points[10]);
    JT_EQUAL(vec[8], points[11]);
    JT_EQUAL(vec[10], points[12]);
    JT_EQUAL(vec[12], points[13]);
    JT_EQUAL(vec[14], points[14]);
}

JT_SUBTEST("Geometry",
           test_CompareXYDirections,
           test_SortBug,
           test_SortClockwiseXY,
           test_SortXY,
           test_SortClockwise);
