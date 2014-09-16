#include "JEBMath/Geometry/SortPoints.hpp"

#include "JEBMath/Geometry/Types.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

void assertLess(const Dim2::DirectionComparer<double>& cmp,
                const Dim2::PointD& p, const Dim2::PointD& q)
{
    JT_ASSERT_MSG(cmp(p, q), p << " not less than " << q);
    JT_ASSERT_MSG(!cmp(q, p), q << " not less than " << p);
}

void test_SortClockwise()
{
    Dim3::LineSegmentD lines[] = {
        Dim3::LineSegmentD(Dim3::pointD(2, 2, 0), Dim3::pointD(0, 0, 3)),
        Dim3::LineSegmentD(Dim3::pointD(2, 2, 0), Dim3::pointD(4, 4, 1)),
        Dim3::LineSegmentD(Dim3::pointD(2, 2, 0), Dim3::pointD(0, 4, 5)),
        Dim3::LineSegmentD(Dim3::pointD(2, 2, 0), Dim3::pointD(4, 0, 1))
    };
    Dim2::sortClockwise(std::begin(lines), std::end(lines), Dim2::pointD(2, 2),
                      [](const Dim3::LineSegmentD& l)
                      {return Dim2::pointD(x(l.end()), y(l.end()));});
    JT_EQUAL(lines[0].end(), Dim3::pointD(4, 4, 1));
    JT_EQUAL(lines[1].end(), Dim3::pointD(0, 4, 5));
    JT_EQUAL(lines[2].end(), Dim3::pointD(0, 0, 3));
    JT_EQUAL(lines[3].end(), Dim3::pointD(4, 0, 1));
}

void test_CompareXYDirections()
{
    Dim2::DirectionComparer<double> cmp(Dim2::pointD(5, 3));
    Dim2::PointD p[] = {
        Dim2::pointD(8, 3),
        Dim2::pointD(7, 3),
        Dim2::pointD(5, 3),
        Dim2::pointD(2, 3),
        Dim2::pointD(1, 3),
        Dim2::pointD(7, 4),
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
    Dim2::PointD p[] = {
        Dim2::pointD(5, 0),
        Dim2::pointD(0, 5),
        Dim2::pointD(-5, 0),
        Dim2::pointD(0, -5),
        Dim2::pointD(4, 3),
        Dim2::pointD(-4, 3),
        Dim2::pointD(-4, -3),
        Dim2::pointD(4, -3),
        Dim2::pointD(3, 4),
        Dim2::pointD(-3, 4),
        Dim2::pointD(-3, -4),
        Dim2::pointD(3, -4),
    };
    Dim2::DirectionComparer<double> cmp(Dim2::pointD(0, 0));
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
    Dim2::PointD points[] = {
        Dim2::pointD(5, 0),
        Dim2::pointD(0, 5),
        Dim2::pointD(-5, 0),
        Dim2::pointD(0, -5),
        Dim2::pointD(4, 3),
        Dim2::pointD(-4, 3),
        Dim2::pointD(-4, -3),
        Dim2::pointD(4, -3),
        Dim2::pointD(3, 4),
        Dim2::pointD(-3, 4),
        Dim2::pointD(-3, -4),
        Dim2::pointD(3, -4),
    };
    std::vector<Dim2::PointD> vec(std::begin(points), std::end(points));
    Dim2::sortClockwise(vec, Dim2::pointD(0, 0));
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
    Dim2::PointD points[] = {
        Dim2::pointD( 0,  0), //  0
        Dim2::pointD(-2,  0), //  1
        Dim2::pointD( 2,  0), //  2
        Dim2::pointD(-2, -1), //  3
        Dim2::pointD(-2,  1), //  4
        Dim2::pointD( 2, -1), //  5
        Dim2::pointD( 2,  1), //  6
        Dim2::pointD(-3, -1), //  7
        Dim2::pointD(-1, -1), //  8
        Dim2::pointD(-3,  1), //  9
        Dim2::pointD(-1,  1), // 10
        Dim2::pointD( 1, -1), // 11
        Dim2::pointD( 3, -1), // 12
        Dim2::pointD( 1,  1), // 13
        Dim2::pointD( 3,  1)  // 14
    };
    std::vector<Dim2::PointD> vec(std::begin(points), std::end(points));
    Dim2::sort(vec.begin(), vec.end());
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
