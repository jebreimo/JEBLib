#include "JEBMath/Geometry/Profile.hpp"
#include "JEBMath/Geometry/ProfileMerger.hpp"

#include <limits>
#include <JEBTest/JEBTest.hpp>
#include "JEBMath/Geometry/LineString.hpp"

using namespace JEBMath;

template <size_t N>
void fill(Profile& ls, double (&array)[N])
{
    for (size_t i = 0; i < N; i += 2)
        ls.push_back(vector2<double>(array[i], array[i + 1]));
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

    Profile ls;
    fill(ls, pnts);
    JT_ASSERT(isProfile(ls));
    JT_EQUAL(ls.size(), 8);
    JT_EQUAL(lowerBound(ls, -1), 0);
    JT_EQUAL(upperBound(ls, -1), 0);
    JT_EQUAL(lowerBound(ls, 0), 0);
    JT_EQUAL(upperBound(ls, 0), 1);
    JT_EQUAL(lowerBound(ls, 2), 1);
    JT_EQUAL(upperBound(ls, 2), 3);
    JT_EQUAL(lowerBound(ls, 6.5), 4);
    JT_EQUAL(upperBound(ls, 6.5), 4);
    JT_EQUAL(lowerBound(ls, 7), 4);
    JT_EQUAL(upperBound(ls, 7), 6);
    JT_EQUAL(lowerBound(ls, 10), 7);
    JT_EQUAL(upperBound(ls, 10), 8);
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

    Profile ls;
    fill(ls, pnts);
    JT_ASSERT(isProfile(ls));
    JT_EQUAL(ls.size(), 8);
    JT_EQUAL(firstSegmentAt(ls, -0.1), JEBMath::InvalidIndex);
    JT_EQUAL(lastSegmentAt(ls, -0.1), JEBMath::InvalidIndex);
    JT_EQUAL(firstSegmentAt(ls, 0), 0);
    JT_EQUAL(lastSegmentAt(ls, 0), 0);
    JT_EQUAL(firstSegmentAt(ls, 2), 0);
    JT_EQUAL(lastSegmentAt(ls, 2), 2);
    JT_EQUAL(firstSegmentAt(ls, 10), 6);
    JT_EQUAL(lastSegmentAt(ls, 10), 6);
    JT_EQUAL(firstSegmentAt(ls, 10.1), getSegmentCount(ls));
    JT_EQUAL(lastSegmentAt(ls, 10.1), getSegmentCount(ls));
}

static void testFirstIsect(const Profile& prof,
                           const Vector<double, 2>& lineSegStart,
                           const Vector<double, 2>& lineSegEnd,
                           const Vector<double, 2>& result)
{
    auto line = makeLineSegment(lineSegStart, lineSegEnd);
    Vector<double, 2> isect;
    JT_ASSERT(firstIntersection(isect, line, prof));
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
    Profile prof;
    fill(prof, pnts);

    Vector<double, 2> (*P)(double x, double y) = vector2<double>;

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
