#ifndef JEBMATH_GEOMETRY_VECTORFUNCTIONS_HPP
#define JEBMATH_GEOMETRY_VECTORFUNCTIONS_HPP

#include <cmath>
#include "../Math/Utilities.hpp"

namespace JEBMath {

template <typename T, typename U, unsigned N>
Vector<T, N>& assignDiv(Vector<T, N>& u, const Vector<U, N>& v)
{
    for (unsigned i = 0; i < N; ++i)
        u[i] /= v[i];
    return u;
}

template <typename T, typename U, unsigned N>
Vector<T, N>& assignMul(Vector<T, N>& u, const Vector<U, N>& v)
{
    for (unsigned i = 0; i < N; ++i)
        u[i] *= v[i];
    return u;
}

template <typename T, typename U, unsigned N>
auto div(const Vector<T, N>& u, const Vector<U, N>& v)
    -> Vector<decltype(u[0] / v[0]), N>
{
    Vector<decltype(u[0] / v[0]), N> w;
    for (unsigned i = 0; i < N; ++i)
        w[i] = u[i] / v[i];
    return w;
}

template <typename T, typename U, unsigned N>
auto div(U scalar, const Vector<T, N>& v)
    -> Vector<decltype(scalar / v[0]), N>
{
    Vector<decltype(scalar / v[0]), N> w;
    for (unsigned i = 0; i < N; ++i)
        w[i] = scalar / v[i];
    return w;
}

template <typename T, typename U, unsigned N>
auto mul(const Vector<T, N>& u, const Vector<U, N>& v)
    -> Vector<decltype(u[0] * v[0]), N>
{
    Vector<decltype(u[0] * v[0]), N> w;
    for (unsigned i = 0; i < N; ++i)
        w[i] = u[i] * v[i];
    return w;
}

template <typename T, unsigned N>
T getLengthSquared(const Vector<T, N>& v)
{
    return v * v;
}

template <typename T, typename U, unsigned N>
bool areEquivalent(const Vector<T, N>& u, const Vector<U, N>& v,
                   double epsilon = 1e-12)
{
    return getLengthSquared(u - v) <= epsilon * epsilon;
}

template <typename T, unsigned N>
double getLength(const Vector<T, N>& v)
{
    return std::sqrt(getLengthSquared(v));
}

template <typename T, unsigned N>
double getCosAngle(const Vector<T, N>& u, const Vector<T, N>& v)
{
    return (u * v) / std::sqrt(getLengthSquared(u) * getLengthSquared(v));
}

template <typename T, typename U, unsigned N>
double getAngle(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return std::acos(getCosAngle(u, v));
}

template <typename T, unsigned N>
Vector<double, N> getUnit(const Vector<T, N>& v)
{
    return v / getLength(v);
}

template <typename T, unsigned N>
Vector<T, N> getResized(const Vector<T, N>& v, T newLength)
{
    return v * (newLength / getLength(v));
}

template <typename T, unsigned N>
void clamp(Vector<T, N>& v, T min, T max)
{
    for (auto i = 0u; i < N; ++i)
        clamp(v[i], min, max);
}

template <typename T, unsigned N>
Vector<T, N> getClamped(Vector<T, N>& v, T min, T max)
{
    clamp(v, min, max);
    return v;
}

template <typename T>
Vector<T, 2> getNormal(const Vector<T, 2>& v)
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
Vector<double, 2> getRotated(const Vector<T, 2>& v, double radians)
{
    auto c = std::cos(radians);
    auto s = std::sin(radians);
    return vector2(v[0] * c - v[1] * s, v[0] * s + v[1] * c);
}

template <typename T, unsigned N>
T& getX(Vector<T, N>& v)
{
    return v[0];
}

template <typename T, unsigned N>
T getX(const Vector<T, N>& v)
{
    return v[0];
}

template <typename T, unsigned N>
void setX(Vector<T, N>& v, T x)
{
    v[0] = x;
}

template <typename T, unsigned N>
T& getY(Vector<T, N>& v)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    return v[1];
}

template <typename T, unsigned N>
T getY(const Vector<T, N>& v)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    return v[1];
}

template <typename T, unsigned N>
void setY(Vector<T, N>& v, T y)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    v[1] = y;
}

template <typename T, unsigned N>
T& getZ(Vector<T, N>& v)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    return v[2];
}

template <typename T, unsigned N>
T getZ(const Vector<T, N>& v)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    return v[2];
}

template <typename T, unsigned N>
void setZ(Vector<T, N>& v, T z)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    v[2] = z;
}

template <typename T, unsigned N>
T& getW(Vector<T, N>& v)
{
    return v[N - 1];
}

template <typename T, unsigned N>
T getW(const Vector<T, N>& v)
{
    return v[N - 1];
}

template <typename T, unsigned N>
void setW(Vector<T, N>& v, T z)
{
    v[N - 1] = z;
}

template <typename T, unsigned N>
void setXY(Vector<T, N>& v, T x, T y)
{
    setX(v, x);
    setY(v, y);
}

template <typename T, unsigned N>
void setXYZ(Vector<T, N>& v, T x, T y, T z)
{
    setX(v, x);
    setY(v, y);
    setZ(v, z);
}

template <typename T, unsigned N>
void setXYZW(Vector<T, N>& v, T x, T y, T z, T w)
{
    static_assert(N > 3, "Vector has less than four coordinates.");
    setX(v, x);
    setY(v, y);
    setZ(v, z);
    setW(v, z);
}

}

#endif
