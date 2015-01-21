#ifndef JEBMATH_GRAPHICS_VECTORFUNCTIONS_HPP
#define JEBMATH_GRAPHICS_VECTORFUNCTIONS_HPP

#include <cmath>
#include "JEBMath/Math/Utilities.hpp"
#include "VectorOperators.hpp"

namespace JEBMath {

template <typename T, typename U, size_t N>
auto inner(const Vector<T, N>& a, const Vector<U, N>& b)
    -> decltype(a[0] * b[0])
{
    auto result = T() * U();
    for (size_t i = 0; i < N; ++i)
        result += a[i] * b[i];
    return result;
}

template <typename T, size_t N>
T lengthSquared(const Vector<T, N>& v)
{
    return inner(v, v);
}

template <typename T, typename U, size_t N>
bool equivalent(const Vector<T, N>& u, const Vector<U, N>& v, double epsilon)
{
    return lengthSquared(u - v) <= epsilon * epsilon;
}

template <typename T, size_t N>
double length(const Vector<T, N>& v)
{
    return std::sqrt(lengthSquared(v));
}

template <typename T, size_t N>
double cosAngle(const Vector<T, N>& u, const Vector<T, N>& v)
{
    return inner(u, v) / std::sqrt(lengthSquared(u) * lengthSquared(v));
}

template <typename T, typename U, size_t N>
double angle(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return std::acos(cosAngle(u, v));
}

template <typename T, size_t N>
Vector<double, N> unit(const Vector<T, N>& v)
{
    return v / length(v);
}

template <typename T, size_t N>
Vector<T, N> resize(const Vector<T, N>& v, T newLength)
{
    return v * (newLength / length(v));
}

template <typename T, size_t N>
void clamp(Vector<T, N>& v, T min, T max)
{
    ;
}

template <typename T>
Vector<T, 2> normal(const Vector<T, 2>& v)
{
    return vector2(-v[1], v[0]);
}

template <typename T, typename U>
auto cross(const Vector<T, 3>& a, const Vector<U, 3>& b)
    -> Vector<decltype(a[0] * b[0]), 3>
{
    return vector3(a[1] * b[2] - a[2] * b[1],
                   a[2] * b[0] - a[0] * b[2],
                   a[0] * b[1] - a[1] * b[0]);
}

template <typename T>
Vector<double, 2> rotate(const Vector<T, 2>& v, double radians)
{
    auto c = std::cos(radians);
    auto s = std::sin(radians);
    return vector2(v[0] * c - v[1] * s, v[1] * s + v[0] * c);
}

}

#endif
