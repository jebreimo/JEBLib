#include "JEBMath/Geometry/LineString.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Basics()
{
    std::vector<Point<int, 2>> ls;
    //typedef Point<int, 2> P;
    ls.push_back(point2<int>(-1, 3));
    ls.push_back(point2<int>(3, 5));
    ls.push_back(point2<int>(7, -4));
    JT_EQUAL(ls.size(), 3);
    JT_EQUAL(segmentCount(ls), 2);
    JT_EQUAL(ls[0], point2<int>(-1, 3));
    JT_EQUAL(ls[2], point2<int>(7, -4));
}

JT_SUBTEST("Geometry", test_Basics);
