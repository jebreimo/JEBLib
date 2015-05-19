#ifndef JEBMATH_GEOMETRY_MATRIXOPERATORS_HPP
#define JEBMATH_GEOMETRY_MATRIXOPERATORS_HPP

#include <ostream>
#include "Vector.hpp"

namespace JEBMath {

template <typename T, typename U, unsigned N>
bool operator==(const Matrix<T, N>& a, const Matrix<U, N>& b)
{
    auto aData = a.data();
    auto bData = b.data();
    for (auto i = 0u; i < N * N; ++i)
    {
        if (aData[i] != bData[i])
            return false;
    }
    return true;
}

template <typename T, typename U, unsigned N>
Matrix<T, N>& operator+=(Matrix<T, N>& a, const Matrix<U, N>& b)
{
    auto dataA = a.data();
    auto dataB = b.data();
    for (auto i = 0u; i < N * N; ++i)
    {
        dataA[i] += dataB[i];
    }
    return a;
}

template <typename T, typename U, unsigned N>
auto operator+(const Matrix<T, N>& a, const Matrix<U, N>& b)
    -> Matrix<decltype(T() + U()), N>
{
    typedef decltype(T() + U()) ResType;
    Matrix<ResType, N> c(a);
    return c += b;
}

template <typename T, typename U, unsigned N>
Matrix<T, N>& operator-=(Matrix<T, N>& a, const Matrix<U, N>& b)
{
    auto dataA = a.data();
    auto dataB = b.data();
    for (auto i = 0u; i < N * N; ++i)
    {
        dataA[i] -= dataB[i];
    }
    return a;
}

template <typename T, typename U, unsigned N>
auto operator-(const Matrix<T, N>& a, const Matrix<U, N>& b)
    -> Matrix<decltype(T() + U()), N>
{
    typedef decltype(T() + U()) ResType;
    Matrix<ResType, N> c(a);
    return c -= b;
}

template <typename T, typename U, unsigned N>
auto operator*(const Matrix<T, N>& a, const Matrix<U, N>& b)
    -> Matrix<decltype(T() * U()), N>
{
    typedef decltype(T() * U()) ResType;
    Matrix<ResType, N> c;
    for (auto i = 0u; i < N; ++i)
    {
        for (auto j = 0u; j < N; ++j)
        {
            ResType v = 0;
            for (auto k = 0u; k < N; ++k)
                v += a[i][k] * b[k][j];
            c[i][j] = v;
        }
    }
    return c;
}

template <typename T, typename U, unsigned N>
Matrix<T, N>& operator*=(Matrix<T, N>& a, const Matrix<U, N>& b)
{
    return a = a * b;
}

template <typename T, typename U, unsigned N>
auto operator*(const Matrix<T, N>& m, const Vector<U, N>& v)
    -> Vector<decltype(T() * U()), N>
{
    typedef decltype(T() * U()) ResType;
    Vector<ResType, N> result;
    for (auto i = 0u; i < N; ++i)
    {
        ResType value = 0;
        for (auto j = 0u; j < N; ++j)
        {
            value += m[i][j] * v[j];
        }
        result[i] = value;
    }
    return result;
}

template <typename T, typename U, unsigned N>
auto operator*(const Vector<T, N>& v, const Matrix<U, N>& m)
    -> Vector<decltype(T() * U()), N>
{
    typedef decltype(T() * U()) ResType;
    Vector<ResType, N> result;
    for (auto i = 0u; i < N; ++i)
    {
        ResType value = 0;
        for (auto j = 0u; j < N; ++j)
        {
            value += v[j] * m[j][i];
        }
        result[i] = value;
    }
    return result;
}

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& m)
{
    os << m[0][0];
    for (auto j = 1u; j < N; ++j)
        os << " " << m[0][j];
    for (auto i = 1u; i < N; ++i)
    {
        os << " |";
        for (auto j = 0u; j < N; ++j)
            os << " " << m[i][j];
    }
    return os;
}

}

#endif
