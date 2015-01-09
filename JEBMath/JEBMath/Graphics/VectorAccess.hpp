#ifndef JEBMATH_GRAPHICS_VECTORASSIGNMENT_HPP
#define JEBMATH_GRAPHICS_VECTORASSIGNMENT_HPP

#include <tuple>
#include "Vector.hpp"

namespace JEBMath {

template <typename T, size_t N>
const T* begin(const Vector<T, N>& v)
{
    return v.begin();
}

template <typename T, size_t N>
const T* end(const Vector<T, N>& v)
{
    return v.end();
}

template <typename T, size_t N>
T* begin(Vector<T, N>& v)
{
    return v.begin();
}

template <typename T, size_t N>
T* end(Vector<T, N>& v)
{
    return v.end();
}

template <typename T>
Vector<T, 2> vector2(T x, T y)
{
    return Vector<T, 2>({x, y});
}

template <typename T>
Vector<T, 3> vector3(T x, T y, T z)
{
    return Vector<T, 3>({x, y, z});
}

template <typename T>
Vector<T, 4> vector4(T x, T y, T z, T w)
{
    return Vector<T, 4>({x, y, z, w});
}

template <typename T, typename U, size_t N>
Vector<T, N> vector(const Vector<U, N>& v)
{
    return Vector<T, N>(v);
}

template <typename T, size_t N>
T& getX(Vector<T, N>& v)
{
    return v[0];
}

template <typename T, size_t N>
T getX(const Vector<T, N>& v)
{
    return v[0];
}

template <typename T, size_t N>
void setX(Vector<T, N>& v, T x)
{
    v[0] = x;
}

template <typename T, size_t N>
T& getY(Vector<T, N>& v)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    return v[1];
}

template <typename T, size_t N>
T getY(const Vector<T, N>& v)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    return v[1];
}

template <typename T, size_t N>
void setY(Vector<T, N>& v, T y)
{
    static_assert(N > 1, "Vector doesn't have a y-coordinate.");
    v[1] = y;
}

template <typename T, size_t N>
T& getZ(Vector<T, N>& v)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    return v[2];
}

template <typename T, size_t N>
T getZ(const Vector<T, N>& v)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    return v[2];
}

template <typename T, size_t N>
void setZ(Vector<T, N>& v, T z)
{
    static_assert(N > 2, "Vector doesn't have a z-coordinate.");
    v[2] = z;
}

template <typename T, size_t N>
T& getW(Vector<T, N>& v)
{
    return v[N - 1];
}

template <typename T, size_t N>
T getW(const Vector<T, N>& v)
{
    return v[N - 1];
}

template <typename T, size_t N>
void setW(Vector<T, N>& v, T z)
{
    v[N - 1] = z;
}

template <typename T, size_t N>
void setXY(Vector<T, N>& v, T x, T y)
{
    setX(v, x);
    setY(v, y);
}

template <typename T, size_t N>
void setXYZ(Vector<T, N>& v, T x, T y, T z)
{
    setX(v, x);
    setY(v, y);
    setZ(v, z);
}

template <typename T, size_t N>
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
