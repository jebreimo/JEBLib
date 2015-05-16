#ifndef JEBMATH_GRAPHICS_VECTOROPERATORS_HPP
#define JEBMATH_GRAPHICS_VECTOROPERATORS_HPP

#include <iostream>
#include "Vector.hpp"

namespace JEBMath {

template <typename T, typename U, size_t N>
bool operator==(const Vector<T, N>& u, const Vector<U, N>& v)
{
    for (size_t i = 0; i < N; ++i)
    {
        if (u[i] != v[i])
            return false;
    }
    return true;
}

template <typename T, typename U, size_t N>
bool operator!=(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return !(u == v);
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator+=(Vector<T, N>& u, const Vector<U, N>& v)
{
    for (size_t i = 0; i < N; ++i)
        u[i] += v[i];
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator+=(Vector<T, N>& u, U scalar)
{
    for (size_t i = 0; i < N; ++i)
        u[i] += scalar;
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator-=(Vector<T, N>& u, const Vector<U, N>& v)
{
    for (size_t i = 0; i < N; ++i)
        u[i] -= v[i];
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator-=(Vector<T, N>& u, U scalar)
{
    for (size_t i = 0; i < N; ++i)
        u[i] -= scalar;
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator*=(Vector<T, N>& u, U scalar)
{
    for (size_t i = 0; i < N; ++i)
        u[i] *= scalar;
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator/=(Vector<T, N>& u, U scalar)
{
    for (size_t i = 0; i < N; ++i)
        u[i] /= scalar;
    return u;
}

template <typename T, size_t N>
Vector<T, N> operator-(Vector<T, N>&& v)
{
    for (size_t i = 0; i < N; ++i)
        v[i] = -v[i];
    return v;
}

template <typename T, size_t N>
Vector<T, N> operator-(const Vector<T, N>& v)
{
    return -Vector<T, N>(v);
}

template <typename T, typename U, size_t N>
auto operator+(const Vector<T, N>& u, const Vector<U, N>& v)
    -> Vector<decltype(u[0] + v[0]), N>
{
    Vector<decltype(u[0] + v[0]), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] + v[i];
    return w;
}

template <typename T, typename U, size_t N>
auto operator+(const Vector<T, N>& u, U scalar)
    -> Vector<decltype(u[0] + scalar), N>
{
    Vector<decltype(u[0] + scalar), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] + scalar;
    return w;
}

template <typename T, typename U, size_t N>
auto operator-(const Vector<T, N>& u, const Vector<U, N>& v)
    -> Vector<decltype(u[0] - v[0]), N>
{
    Vector<decltype(u[0] - v[0]), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] - v[i];
    return w;
}

template <typename T, typename U, size_t N>
auto operator-(const Vector<T, N>& u, U scalar)
    -> Vector<decltype(u[0] - scalar), N>
{
    Vector<decltype(u[0] - scalar), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] - scalar;
    return w;
}

template <typename T, typename U, size_t N>
auto operator/(const Vector<T, N>& u, U scalar)
    -> Vector<decltype(u[0] / scalar), N>
{
    Vector<decltype(u[0] / scalar), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] / scalar;
    return w;
}

template <typename T, typename U, size_t N>
auto operator*(const Vector<T, N>& u, const Vector<U, N>& v)
    -> decltype(u[0] * v[0])
{
    auto result = T() * U();
    for (size_t i = 0; i < N; ++i)
        result += u[i] * v[i];
    return result;
}

template <typename T, typename U, size_t N>
auto operator*(const Vector<T, N>& u, U scalar)
    -> Vector<decltype(u[0] * scalar), N>
{
    Vector<decltype(u[0] * scalar), N> w;
    for (size_t i = 0; i < N; ++i)
        w[i] = u[i] * scalar;
    return w;
}

template <typename T, typename U, size_t N>
auto operator*(U scalar, const Vector<T, N>& v)
    -> Vector<decltype(v[0] + scalar), N>
{
    return v * scalar;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v)
{
    const T* it = v.begin();
    os << "[" << *it;
    while (++it != v.end())
        os << " " << *it;
    return os << "]";
}

}

#endif
