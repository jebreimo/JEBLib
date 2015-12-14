#ifndef JEBMATH_GEOMETRY_HOMOGENEOUSTRANSFORMS_HPP
#define JEBMATH_GEOMETRY_HOMOGENEOUSTRANSFORMS_HPP

#include "Matrix.hpp"

namespace JEBMath { namespace HomogeneousTransforms {

template <typename T, unsigned N>
Matrix<T, N> scale(T s)
{
    Matrix<T, N> m;
    for (unsigned i = 0; i < N - 1; ++i)
        m[i][i] = s;
    m[N - 1][N - 1] = 1;
    return m;
}

template <typename T, unsigned N>
Matrix<T, N> scale(const Vector<T, N - 1>& s)
{
    Matrix<T, N> m;
    for (unsigned i = 0; i < N - 1; ++i)
        m[i][i] = s[i];
    m[N - 1][N - 1] = 1;
    return m;
}

template <typename T, unsigned N>
Matrix<T, N> rotateZ(T angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    Matrix<T, N> m;
    m[0][0] = m[1][1] = c;
    m[0][1] = -s;
    m[1][0] = s;
    for (unsigned i = 2; i < N; ++i)
        m[i][i] = 1;
    return m;
}

template <typename T, unsigned N>
Matrix<T, N> rotateZT(T angle)
{
    auto m = rotateZ(angle);
    m[0][1] = -m[0][1];
    m[1][0] = -m[1][0];
    return m;
}

template <typename T>
Matrix<T, 4> rotateY4(T angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<T, 4>{ c, 0, s, 0,
                         0, 1, 0, 0,
                        -s, 0, c, 0,
                         0, 0, 0, 1};
}

template <typename T>
Matrix<T, 4> rotateY4T(T angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<T, 4>{c, 0, -s, 0,
                        0, 1,  0, 0,
                        s, 0,  c, 0,
                        0, 0,  0, 1};
}

template <typename T>
Matrix<T, 4> rotateX4(T angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<T, 4>{1,  0, 0, 0,
                        0,  c, s, 0,
                        0, -s, c, 0,
                        0,  0, 0, 1};
}

template <typename T>
Matrix<T, 4> rotateX4T(T angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<T, 4>{1, 0,  0, 0,
                        0, c, -s, 0,
                        0, s,  c, 0,
                        0, 0,  0, 1};
}

template <typename T>
Matrix<T, 4> rotate4(T angle, const Vector<T, 3>& axis)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    auto cx = axis * ((1 - c) * axis[0]);
    auto cy = axis * ((1 - c) * axis[1]);
    auto cz = axis * ((1 - c) * axis[2]);
    auto sa = s * axis;
    return Matrix<T, 4>{cx[0] + c,     cx[1] - sa[2], cx[2] + sa[1], 0,
                        cy[0] + sa[2], cy[1] + c,     cy[2] - sa[0], 0,
                        cz[0] - sa[1], cz[1] + sa[0], cz[2] + c,     0,
                                    0,             0,         0,     1};
}

template <typename T>
Matrix<T, 4> rotate4T(T angle, const Vector<T, 3>& axis)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    auto cx = axis * ((1 - c) * axis[0]);
    auto cy = axis * ((1 - c) * axis[1]);
    auto cz = axis * ((1 - c) * axis[2]);
    auto sa = s * axis;
    return Matrix<T, 4>{cx[0] + c,     cy[0] + sa[2], cz[0] - sa[1], 0,
                        cx[1] - sa[2], cy[1] + c,     cz[1] + sa[0], 0,
                        cx[2] + sa[1], cy[2] - sa[0], cz[2] + c,     0,
                                    0,             0,         0,     1};
}

template <typename T, unsigned N>
Matrix<T, N> translate(const Vector<T, N - 1>& offsets)
{
    Matrix<T, N> m;
    for (unsigned i = 0; i < N - 1; ++i)
    {
        m[i][i] = 1;
        m[i][N - 1] = offsets[i];
    }
    m[N - 1][N - 1] = 1;
    return m;
}

template <typename T, unsigned N>
Matrix<T, N> translateT(const Vector<T, N - 1>& offsets)
{
    Matrix<T, N> m;
    for (unsigned i = 0; i < N; ++i)
        m[i][i] = 1;
    for (unsigned i = 0; i < N - 1; ++i)
        m[N - 1][i] = offsets[i];
    return m;
}

}}

#endif
