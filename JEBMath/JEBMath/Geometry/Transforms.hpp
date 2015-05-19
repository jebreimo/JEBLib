#ifndef JEBMATH_TRANSFORMS_HPP
#define JEBMATH_TRANSFORMS_HPP

#include <cmath>
#include "Matrix.hpp"
#include "Vector.hpp"

namespace JEBMath { namespace Transforms {

template <unsigned N>
Matrix<double, N> scale(double s)
{
    Matrix<double, N> m;
    for (auto i = 0u; i < N - 1; ++i)
        m[i][i] = s;
    m[N - 1][N - 1] = 1;
    return m;
}

template <unsigned N>
Matrix<double, N + 1> scale(Vector<double, N>& scales)
{
    Matrix<double, N + 1> m;
    for (auto i = 0u; i < N; ++i)
        m[i][i] = scales[i];
    m[N][N] = 1;
    return m;
}

template <unsigned N>
Matrix<double, N> rotateZ(double angle)
{
    static_assert(N > 1, "Matrix must be of dimension 2 or greater.");
    Matrix<double, N> m;
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    m[0][0] = c;
    m[0][1] = -s;
    m[1][0] = s;
    m[1][1] = c;
    for (auto i = 2u; i < N; ++i)
        m[i][i] = 1;
    return m;
}

template <unsigned N>
Matrix<double, N> rotateY(double angle)
{
    static_assert(N > 2, "Matrix must be of dimension 3 or greater.");
    Matrix<double, N> m;
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    m[0][0] = c;
    m[0][2] = s;
    m[1][1] = 1;
    m[2][0] = -s;
    m[2][2] = c;
    for (auto i = 3u; i < N; ++i)
        m[i][i] = 1;
    return m;
}

template <unsigned N>
Matrix<double, 4> rotateX(double angle)
{
    static_assert(N > 2, "Matrix must be of dimension 3 or greater.");
    Matrix<double, N> m;
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    m[0][0] = 1;
    m[1][1] = c;
    m[1][2] = -s;
    m[2][1] = s;
    m[2][2] = c;
    for (auto i = 3u; i < N; ++i)
        m[i][i] = 1;
    return m;
}

}}

#endif
