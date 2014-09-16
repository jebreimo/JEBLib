#include "JEBBase/Containers/Array2D.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Containers;

typedef std::pair<size_t, size_t> Size;

void test_Basics()
{
    Array2D<double> a(5, 7);
    JT_EQUAL(a.size(), Size(5, 7));
    JT_EQUAL(a[0][0], 0);
    JT_EQUAL(a[4][4], 0);
    JT_EQUAL(a[3][3], 0);
    a[3][3] = 4.75;
    JT_EQUAL(a[3][3], 4.75);

    Array2D<double> b = a;
    JT_EQUAL(b.size(), Size(5, 7));
    JT_EQUAL(b[3][3], 4.75);

    b[2][6] = 42;
    JT_EQUAL(b[2][6], 42);
    JT_EQUAL(a[2][6], 0);

    JT_EQUAL(a[4][6], 0);
    a[4][6] = 100;
    JT_EQUAL(a[4][6], 100);

    JT_EQUAL(b[4][6], 0);
    b = a;
    JT_EQUAL(b[4][6], 100);

    Array2D<double> c;
    JT_EQUAL(c.size(), Size(0, 0));
    c.setSize(2, 4);
    JT_EQUAL(c.size(), Size(2, 4));
    c = a;
    JT_EQUAL(c.size(), Size(5, 7));
    JT_EQUAL(c[4][6], 100);
}

JT_SUBTEST("Containers", test_Basics);
