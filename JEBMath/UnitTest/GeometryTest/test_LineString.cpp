#include "JEBMath/Geometry/LineString.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Basics()
{
    std::vector<Vector<int, 2>> ls;
    ls.push_back(vector2(-1, 3));
    ls.push_back(vector2(3, 5));
    ls.push_back(vector2(7, -4));
    JT_EQUAL(getSegmentCount(ls), 2);
}

JT_SUBTEST("Geometry", test_Basics);
