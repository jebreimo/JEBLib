#include "JEBBase/Containers/CircularArray2D.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBBase::Containers;

typedef std::pair<size_t, size_t> Size;

void test_Basics()
{
    CircularArray2D<double> a(4, 4);
    JT_EQUAL(a.size(), Size(4, 4));
    JT_EQUAL(a[0][0], 0);
    JT_EQUAL(a[2][1], 0);
    JT_EQUAL(a[4][4], 0);

    a[0][0] = 10;
    JT_EQUAL(a[0][0], 10);
    JT_EQUAL(a[2][1], 0);
    JT_EQUAL(a[3][3], 0);
    JT_EQUAL(a[4][4], 10);
    JT_EQUAL(a[8][8], 10);
}

JT_SUBTEST("Containers", test_Basics);

}
