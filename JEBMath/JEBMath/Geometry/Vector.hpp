#ifndef JEBMATH_GEOMETRY_VECTOR_HPP
#define JEBMATH_GEOMETRY_VECTOR_HPP

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iosfwd>
#include <numeric>
#include <stdexcept>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

template <typename T, size_t N>
class Point;

template <typename T, size_t N>
class Vector
{
public:
    static const size_t Dimension = N;
    static const size_t dimension() {return N;}

    Vector()
    {
        std::fill(&m_Coords[0], &m_Coords[N], 0);
    }

    Vector(std::initializer_list<T> v)
    {
        if (v.size() != N)
            throw std::invalid_argument("Incorrect number of arguments.");
        std::copy(v.begin(), v.end(), std::begin(m_Coords));
    }

    Vector(T (&arr)[N])
    {
        std::copy(&arr[0], &arr[N], m_Coords);
    }

    template <typename U>
    explicit Vector(const Point<U, N>& point)
    {
        std::copy(point.begin(), point.end(), m_Coords);
    }

    template <typename U>
    explicit Vector(const Vector<U, N>& other)
    {
        std::copy(other.begin(), other.end(), m_Coords);
    }

    template <typename U>
    Vector<T, N>& operator=(const Vector<U, N>& other)
    {
        std::copy(other.begin(), other.end(), m_Coords);
        return *this;
    }

    template <typename U>
    operator Vector<U, N>() const
    {
        return Vector<U, N>(*this);
    }

    explicit operator bool() const
    {
        return std::all_of(std::begin(m_Coords), std::end(m_Coords),
                           [](T v){return bool(v);});
    }

    const T& operator[](size_t i) const
    {
        return m_Coords[i];
    }

    T& operator[](size_t i)
    {
        return m_Coords[i];
    }

    const T* begin() const
    {
        return &m_Coords[0];
    }

    T* begin()
    {
        return &m_Coords[0];
    }

    const T* end() const
    {
        return &m_Coords[N];
    }

    T* end()
    {
        return &m_Coords[N];
    }
private:
    T m_Coords[N];
};

template <typename T, typename U, size_t N>
bool operator==(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return std::equal(u.begin(), u.end(), v.begin());
}

template <typename T, typename U, size_t N>
bool operator!=(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return !(u == v);
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator+=(Vector<T, N>& u, const Vector<U, N>& v)
{
    std::transform(u.begin(), u.end(), v.begin(), u.begin(),
                   [](T a, U b){return T(a + b);});
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator-=(Vector<T, N>& u, const Vector<U, N>& v)
{
    std::transform(u.begin(), u.end(), v.begin(), u.begin(),
                   [](T a, U b){return T(a - b);});
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator*=(Vector<T, N>& u, U scalar)
{
    std::transform(u.begin(), u.end(), u.begin(),
                   [&](T t){return T(t * scalar);});
    return u;
}

template <typename T, typename U, size_t N>
Vector<T, N>& operator/=(Vector<T, N>& u, U scalar)
{
    std::transform(u.begin(), u.end(), u.begin(),
                   [&](T t){return T(t / scalar);});
    return u;
}

template <typename T, size_t N>
Vector<T, N> operator-(Vector<T, N>&& v)
{
    std::transform(v.begin(), v.end(), v.begin(), [](T a){return -a;});
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
    std::transform(u.begin(), u.end(), v.begin(), w.begin(),
                   [](T a, U b){return a + b;});
    return w;
}

template <typename T, typename U, size_t N>
auto operator-(const Vector<T, N>& u, const Vector<U, N>& v)
    -> Vector<decltype(u[0] - v[0]), N>
{
    Vector<decltype(u[0] - v[0]), N> w;
    std::transform(u.begin(), u.end(), v.begin(), w.begin(),
                   [](T a, U b){return a - b;});
    return w;
}

template <typename T, typename U, size_t N>
auto operator/(const Vector<T, N>& v, U scalar)
    -> Vector<decltype(v[0] / scalar), N>
{
    Vector<decltype(v[0] / scalar), N> w;
    std::transform(v.begin(), v.end(), w.begin(),
                   [&](T a){return a / scalar;});
    return w;
}

template <typename T, typename U, size_t N>
auto operator/(U scalar, const Vector<T, N>& v)
    -> Vector<decltype(scalar / v[0]), N>
{
    Vector<decltype(scalar / v[0]), N> w;
    std::transform(v.begin(), v.end(), w.begin(),
                   [&](T a){return scalar / a;});
    return w;
}

template <typename T, typename U, size_t N>
auto operator*(const Vector<T, N>& v, U scalar)
    -> Vector<decltype(v[0] * scalar), N>
{
    Vector<decltype(v[0] * scalar), N> w;
    std::transform(v.begin(), v.end(), w.begin(),
                   [&](T a){return a * scalar;});
    return w;
}

template <typename T, typename U, size_t N>
auto operator*(U scalar, const Vector<T, N>& v)
    -> Vector<decltype(v[0] + scalar), N>
{
    return v * scalar;
}

template <typename T, typename U, size_t N>
auto operator*(const Vector<T, N>& u, const Vector<U, N>& v)
    -> decltype(u[0] * v[0])
{
    return std::inner_product(u.begin(), u.end(), v.begin(), (T)0);
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v);

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

template <typename T, typename U, size_t N>
bool equivalent(const Vector<T, N>& u, const Vector<U, N>& v, double epsilon);

template <typename T, size_t N>
double length(const Vector<T, N>& v);

template <typename T, size_t N>
T lengthSquared(const Vector<T, N>& v);

template <typename T, size_t N>
Vector<double, N> unit(const Vector<T, N>& v);

template <typename T, size_t N>
double cosAngle(const Vector<T, N>& u, const Vector<T, N>& v);

template <typename T, typename U, size_t N>
double angle(const Vector<T, N>& u, const Vector<U, N>& v);

template <typename T, size_t N>
Vector<T, N> resize(const Vector<T, N>& v, T newLength) {return v * (newLength / length(v));}

template <typename T>
Vector<T, 2> normal(const Vector<T, 2>& v);

template <typename T>
Vector<T, 2> vector2(T x, T y) {return Vector<T, 2>({x, y});}

template <typename T>
Vector<T, 2> vector2(const std::pair<T, T>& p) {return Vector<T, 2>({p.first, p.second});}

template <typename T>
Vector<T, 3> vector3(T x, T y, T z) {return Vector<T, 3>({x, y, z});}

template <typename T>
Vector<T, 4> vector4(T x, T y, T z, T w) {return Vector<T, 4>({x, y, z, w});}

template <typename T, size_t N>
Vector<T, N> vector(const Point<T, N>& p)
{
    return Vector<T, N>(p);
}

template <typename T, typename U, size_t N>
Vector<T, N> vector(const Vector<U, N>& v)
{
    return Vector<T, N>(v);
}

template <typename T>
T& x(Vector<T, 2>& v) {return v[0];}
template <typename T>
T x(const Vector<T, 2>& v) {return v[0];}
template <typename T>
void setX(Vector<T, 2>& v, T x) {v[0] = x;}

template <typename T>
T& y(Vector<T, 2>& v) {return v[1];}
template <typename T>
T y(const Vector<T, 2>& v) {return v[1];}
template <typename T>
void setY(Vector<T, 2>& v, T y) {v[1] = y;}

template <typename T>
T& x(Vector<T, 3>& v) {return v[0];}
template <typename T>
T x(const Vector<T, 3>& v) {return v[0];}
template <typename T>
void setX(Vector<T, 3>& v, T x) {v[0] = x;}

template <typename T>
T& y(Vector<T, 3>& v) {return v[1];}
template <typename T>
T y(const Vector<T, 3>& v) {return v[1];}
template <typename T>
void setY(Vector<T, 3>& v, T y) {v[1] = y;}

template <typename T>
T& z(Vector<T, 3>& v) {return v[2];}
template <typename T>
T z(const Vector<T, 3>& v) {return v[2];}
template <typename T>
void setZ(Vector<T, 3>& v, T z) {v[2] = z;}

template <typename T>
void setXY(Vector<T, 2>& v, T x, T y) {setX(v, x); setY(v, y);}

template <typename T>
void setXYZ(Vector<T, 3>& v, T x, T y, T z) {setX(v, x); setY(v, y); setZ(v, z);}

template <typename T, typename U>
auto cross(const Vector<T, 3>& a, const Vector<U, 3>& b)
    -> Vector<decltype(a[0] * b[0]), 3>
{
    return vector3(a[1] * b[2] - a[2] * b[1],
                   a[2] * b[0] - a[0] * b[2],
                   a[0] * b[1] - a[1] * b[0]);
}

/** @brief Returns a vector whose coordinates are the products of the
 *      corresponding coordinates in @a u and @a v.
 */
template <typename T, typename U, size_t N>
auto scale(const Vector<T, N>& v, const Vector<U, N>& scales)
    -> Vector<decltype(v[0] * scales[0]), N>
{
    Vector<decltype(v[0] * scales[0]), N> result;
    std::transform(begin(v), end(v), begin(scales), begin(result),
                   [](T a, U b){return a * b;});
    return result;
}

template <typename T>
Vector<double, 2> rotate(const Vector<T, 2>& v, double radians);

}

#include "Vector.impl.hpp"

#endif
