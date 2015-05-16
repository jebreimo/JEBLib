#include "JEBMath/JEBVectorMath.hpp"

#include <cmath>
#include <JEBTest/JEBTest.hpp>
#include "JEBMath/Math/Utilities.hpp"

namespace {

using namespace JEBMath;

void test_Basics()
{
    auto mat = Matrix<double, 3>{1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1};
    JT_EQUAL(mat[0][0], 1);
    JT_EQUAL(mat[0][1], 0);
    JT_EQUAL(mat[1][1], 1);
}

void test_Transpose()
{
    auto mat1 = Matrix<double, 4>{0, 1, 2, 3,
                                  4, 5, 6, 7,
                                  8, 9, 0, 1,
                                  2, 3, 4, 5};
    auto mat1t = Matrix<double, 4>{0, 4, 8, 2,
                                   1, 5, 9, 3,
                                   2, 6, 0, 4,
                                   3, 7, 1, 5};
    JT_EQUAL(transposed(mat1), mat1t);
    transpose(mat1t);
    JT_EQUAL(mat1, mat1t);
}

void test_MatrixMatrixAddition()
{
    typedef Matrix<int, 3> Mat;
    auto m1 = Mat{1, 2, 3,
                  4, 5, 6,
                  7, 8, 9};
    auto m2 = Mat{ 1, -1,  1,
                  -1,  1, -1,
                   1, -1,  1};
    auto product =  Mat{ 2,  1,  4,
                         3,  6,  5,
                         8,  7, 10};
    JT_EQUAL(m1 + m2, product);
}

void test_MatrixMatrixSubtraction()
{
    typedef Matrix<int, 3> Mat;
    auto m1 = Mat{1, 2, 3,
                  4, 5, 6,
                  7, 8, 9};
    auto m2 = Mat{ 1, -1,  1,
                  -1,  1, -1,
                   1, -1,  1};
    auto product =  Mat{0, 3, 2,
                        5, 4, 7,
                        6, 9, 8};
    JT_EQUAL(m1 - m2, product);
}

void test_MatrixMatrixMultiplication()
{
    typedef Matrix<int, 2> Mat;
    auto m1 = Mat{1, 2,
                  3, 4};
    auto m2 = Mat{4, 3,
                  1, 2};
    auto product =  Mat{ 6,  7,
                        16, 17};
    JT_EQUAL(m1 * m2, product);
}

void test_MatrixVectorMultiplication()
{
    auto m = Matrix<int, 3>{1, 2, 3,
                            4, 5, 6,
                            7, 8, 9};
    auto v = Vector<int, 3>{1, 2, 3};
    auto product1 =  Vector<int, 3>{14, 32, 50};
    auto product2 =  Vector<int, 3>{30, 36, 42};
    JT_EQUAL(m * v, product1);
    JT_EQUAL(v * m, product2);
}

JT_SUBTEST("Graphics",
           test_Basics,
           test_Transpose,
           test_MatrixMatrixAddition,
           test_MatrixMatrixSubtraction,
           test_MatrixMatrixMultiplication,
           test_MatrixVectorMultiplication);
}
