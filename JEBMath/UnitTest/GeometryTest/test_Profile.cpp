// #include "JEBMath/Geometry/JEBMath.hpp"
#include "JEBMath/Geometry/Types.hpp"
#include "JEBMath/Geometry/Profile.hpp"
#include "JEBMath/Geometry/ProfileMerger.hpp"

#include <limits>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;
using namespace JEBMath::Dim2;

template <size_t N>
void fill(LineStringD& ls, double (&array)[N])
{
    for (size_t i = 0; i < N; i += 2)
        ls.push_back(point2<double>(array[i], array[i + 1]));
}

static void test_Bounds()
{
    double pnts[] = {
        0, 0,
        2, 1,
        2, 2,
        3, 3,
        7, 4,
        7, 5,
        8, 6,
       10, 7
    };

    LineStringD ls;
    fill(ls, pnts);
    JT_ASSERT(Profile::isProfile(ls));
    JT_EQUAL(ls.size(), 8);
    JT_EQUAL(Profile::lowerBound(ls, -1), 0);
    JT_EQUAL(Profile::upperBound(ls, -1), 0);
    JT_EQUAL(Profile::lowerBound(ls, 0), 0);
    JT_EQUAL(Profile::upperBound(ls, 0), 1);
    JT_EQUAL(Profile::lowerBound(ls, 2), 1);
    JT_EQUAL(Profile::upperBound(ls, 2), 3);
    JT_EQUAL(Profile::lowerBound(ls, 6.5), 4);
    JT_EQUAL(Profile::upperBound(ls, 6.5), 4);
    JT_EQUAL(Profile::lowerBound(ls, 7), 4);
    JT_EQUAL(Profile::upperBound(ls, 7), 6);
    JT_EQUAL(Profile::lowerBound(ls, 10), 7);
    JT_EQUAL(Profile::upperBound(ls, 10), 8);
}

static void test_SegmentAt()
{
    double pnts[] = {
        0, 0,
        2, 1,
        2, 2,
        3, 3,
        7, 4,
        7, 5,
        8, 6,
       10, 7
    };

    LineStringD ls;
    fill(ls, pnts);
    JT_ASSERT(Profile::isProfile(ls));
    JT_EQUAL(ls.size(), 8);
    JT_EQUAL(Profile::firstSegmentAt(ls, -0.1), JEBMath::InvalidIndex);
    JT_EQUAL(Profile::lastSegmentAt(ls, -0.1), JEBMath::InvalidIndex);
    JT_EQUAL(Profile::firstSegmentAt(ls, 0), 0);
    JT_EQUAL(Profile::lastSegmentAt(ls, 0), 0);
    JT_EQUAL(Profile::firstSegmentAt(ls, 2), 0);
    JT_EQUAL(Profile::lastSegmentAt(ls, 2), 2);
    JT_EQUAL(Profile::firstSegmentAt(ls, 10), 6);
    JT_EQUAL(Profile::lastSegmentAt(ls, 10), 6);
    JT_EQUAL(Profile::firstSegmentAt(ls, 10.1), segmentCount(ls));
    JT_EQUAL(Profile::lastSegmentAt(ls, 10.1), segmentCount(ls));
}

static void testFirstIsect(const LineStringD& prof,
                           const PointD& lineSegStart,
                           const PointD& lineSegEnd,
                           const PointD& result)
{
    LineSegmentD line(lineSegStart, lineSegEnd);
    PointD isect;
    JT_ASSERT(Profile::firstIntersection(isect, line, prof));
    JT_EQUAL(isect, result);
}

static void test_FirstIntersection()
{
    double pnts[] = {
         0, 0,
         3, 3,
         6, 0,
         9, 3,
         9, 0,
        12, 0
    };
    LineStringD prof;
    fill(prof, pnts);

    Point<double, 2> (*P)(double x, double y) = point2<double>;

    testFirstIsect(prof, P(4, 2), P(7, 1), P(4, 2));
    testFirstIsect(prof, P(7, 1), P(4, 2), P(7, 1));
    testFirstIsect(prof, P(2, 4), P(7, -1), P(3, 3));
    testFirstIsect(prof, P(0, 1), P(3, 2), P(1.5, 1.5));
    testFirstIsect(prof, P(4, 1), P(4, 8), P(4, 2));
    testFirstIsect(prof, P(9, 1), P(9, 8), P(9, 1));
    testFirstIsect(prof, P(9, -1), P(9, 8), P(9, 0));
    testFirstIsect(prof, P(9, 7), P(9, 1), P(9, 3));
}

JT_SUBTEST("Geometry",
           test_Bounds,
           test_SegmentAt,
           test_FirstIntersection);
