#include "JEBMath/Math/CubicFunction.hpp"
#include <JEBTest/JEBTest.hpp>
#include <utility>

using namespace JEBMath;
using namespace std;

static void sortValues(double& a, double& b)
{
    if (a > b)
        swap(a, b);
}

static void sortValues(double& a, double& b, double& c)
{
    sortValues(a, b);
    sortValues(b, c);
    sortValues(a, b);
}

static void testRoots(double root1, double root2, double root3, double epsilon = 1e-12)
{
    sortValues(root1, root2, root3);

    double a = 1;
    double b = -(root1 + root2 + root3);
    double c = root1 * (root2 + root3) + root2 * root3;
    double d = -root1 * root2 * root3;
    CubicFunction cf(a, b, c, d);
    JT_EQUAL(cf.a(), a);
    JT_EQUAL(cf.b(), b);
    JT_EQUAL(cf.c(), c);
    JT_EQUAL(cf.d(), d);
    size_t expectedSolutions = 1
                             + (root1 != root2 ? 1 : 0)
                             + (root2 != root3 ? 1 : 0);
    double t[3];
    size_t solutions = cf.roots(t);
    JT_EQUAL(solutions, expectedSolutions);
    if (solutions == 2)
        sortValues(t[0], t[1]);
    if (solutions == 3)
        sortValues(t[0], t[1], t[2]);
    size_t i = 0;
    JT_EQUIVALENT(t[i], root1, epsilon);
    i++;
    if (solutions > i && root2 != root1)
    {
        JT_EQUIVALENT(t[i], root2, epsilon);
        i++;
    }
    if (solutions > i && root3 != root2)
        JT_EQUIVALENT(t[i], root3, epsilon);
    JT_ASSERT(cf.root(0, t[0]));
    JT_ASSERT(cf.root(1, t[1]));
    JT_ASSERT(cf.root(2, t[2]));
    sortValues(t[0], t[1], t[2]);
    JT_EQUIVALENT(t[0], root1, epsilon);
    JT_EQUIVALENT(t[1], root2, epsilon);
    JT_EQUIVALENT(t[2], root3, epsilon);
}

static void test_Roots()
{
    testRoots(0, 0, 0);
    testRoots(-1, 2, 2);
    testRoots(1, 2, 3);
    testRoots(1, 200, 39876, 1e-9);
}

JT_SUBTEST("Math", test_Roots);
