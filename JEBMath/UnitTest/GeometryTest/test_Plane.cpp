#include "JEBMath/Geometry/Plane.hpp"
#include "JEBMath/Geometry/Types.hpp"
#include <cmath>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_Units()
{
    Plane3<double> plane1(Dim3::pointD(1, 1, 1), Dim3::vectorD(1, 1, 1));
    Dim3::VectorD u1, u2;
    JT_ASSERT(plane1.getUnitVectors(u1, u2));

    JT_ASSERT(equivalent(
            u1,
            Dim3::vectorD(-1 / std::sqrt(2.0),  1 / std::sqrt(2.0), 0),
            1e-10));
    JT_ASSERT(equivalent(
            u2,
            Dim3::vectorD(-1 / std::sqrt(6.0), -1 / std::sqrt(6.0), std::sqrt(2.0 / 3.0)),
            1e-10));
}

JT_SUBTEST("Geometry", test_Units);
