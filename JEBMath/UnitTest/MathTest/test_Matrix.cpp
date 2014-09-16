#include "JEBMath/Math/Matrix.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

namespace {

template <typename T>
void assertValue(const Matrix<T>& m,
                        size_t i,
                        size_t j,
                        T value)
{
    JT_ASSERT_MSG(m[i][j] == value,
                  "unexpected value at " << i << ", " << j << ": "
                  << m[i][j] << " (expected " << value << ")");
}

template <typename T>
void assertValues(const Matrix<T>& m,
                         T firstValue,
                         T increment)
{
    T value = firstValue;
    for (size_t i = 0; i < m.rows(); i++)
    {
        for (size_t j = 0; j < m.columns(); j++)
        {
            assertValue<T>(m, i, j, value);
            value += increment;
        }
    }
}

template <typename T>
void init(Matrix<T>& m, T firstValue = 0, T increment = 1)
{
    for (auto it = m.begin(); it != m.end(); it++)
    {
        *it = firstValue;
        firstValue += increment;
    }
}

void test_Initialization()
{
    Matrix<double> matrix(4, 6);
    JT_EQUAL(matrix.rows(), 4);
    JT_EQUAL(matrix.columns(), 6);
    JT_EQUAL(matrix.size().first, matrix.rows());
    JT_EQUAL(matrix.size().second, matrix.columns());
    for (size_t i = 0; i < matrix.rows(); i++)
        for (size_t j = 0; j < matrix.columns(); j++)
            assertValue<double>(matrix, i, j, 0);
    double value = 0;
    for (Matrix<double>::iterator it = matrix.begin(); it != matrix.end(); it++)
    {
        *it = value;
        value += 1;
    }
    assertValues(matrix, 0.0, 1.0);
    matrix[2][4] = 5;
    assertValue<double>(matrix, 2, 4, 5);
}

void test_Add()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    Matrix<int> m2(4, 5);
    JT_THROWS(m += m2, std::invalid_argument);
    Matrix<int> m3(3, 5);
    std::fill(m3.begin(), m3.end(), 1);
    m += m3;
    assertValues(m, 1, 1);
}

void test_Sub()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    Matrix<int> m2(4, 5);
    JT_THROWS(m -= m2, std::invalid_argument);
    Matrix<int> m3(3, 5);
    std::fill(m3.begin(), m3.end(), 1);
    JT_EQUAL(m[0][0], 0);
    JT_EQUAL(m3[0][0], 1);
    m3 -= m;
    assertValues(m3, 1, -1);
}

void test_Mul()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    m *= 7;
    assertValues(m, 0, 7);
}

void test_Transpose()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    m.transpose();
    JT_EQUAL(m.rows(), 5);
    JT_EQUAL(m.columns(), 3);
    for (size_t i = 0; i < m.rows(); i++)
        for (size_t j = 0; j < m.columns(); j++)
            assertValue<int>(m, i, j, int(j * m.rows() + i));
}

void test_Negation()
{
    Matrix<int> m(2, 2);
    init(m);
    assertValues(-m, 0, -1);
}

void test_Turn()
{
    Matrix<int> m(3, 4);
    auto n = 0;
    for (auto& v : m)
        v = n++;
    m.turn(1);
    JT_EQUAL(m.rows(), 4);
    JT_EQUAL(m.columns(), 3);
    for (auto i = 0; i < m.rows(); i++)
        for (auto j = 0; j < m.columns(); j++)
            assertValue<int>(m, i, j, int((3 - i) + j  * m.rows()));
}

JT_SUBTEST("Math",
           test_Initialization,
           test_Add,
           test_Sub,
           test_Mul,
           test_Transpose,
           test_Negation,
           test_Turn);
}
