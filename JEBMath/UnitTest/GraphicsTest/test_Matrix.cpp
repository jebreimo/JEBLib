#include "JEBMath/Graphics/Matrix.hpp"

#include <cmath>
#include <JEBTest/JEBTest.hpp>
#include "JEBMath/Math/Utilities.hpp"

namespace {

using namespace JEBMath;

void test_Basics()
{
    Matrix<double, 3> mat = {1, 0, 0,
                             0, 1, 0,
                             0, 0, 1};
    JT_EQUAL(mat[0][0], 1);
    JT_EQUAL(mat[0][1], 0);
    JT_EQUAL(mat[1][1], 1);
}

JT_SUBTEST("Graphics",
           test_Basics);
}
