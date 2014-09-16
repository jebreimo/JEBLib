#ifndef JEBMATH_GEOMETRY_POINT_HPP
#define JEBMATH_GEOMETRY_POINT_HPP

#include <algorithm>
#include <initializer_list>
#include <iosfwd>
#include <stdexcept>
#include "JEBMath/Math/Constants.hpp"

namespace JEBMath {

template <typename T, size_t N>
class Vector;

template <typename T, size_t N>
class Point
{
public:
    typedef T value_type;
    static const size_t Dimension = N;
    static const size_t dimension() {return N;}

    Point()
    {
        std::fill(&m_Coords[0], &m_Coords[N], 0);
    }

    Point(std::initializer_list<T> v)
    {
        if (v.size() != N)
            throw std::invalid_argument("Incorrect number of arguments.");
        std::copy(v.begin(), v.end(), std::begin(m_Coords));
    }

    Point(T (&arr)[N])
    {
        std::copy(&arr[0], &arr[N], m_Coords);
    }

    template <typename U>
    explicit Point(const Vector<U, N>& v)
    {
        std::copy(v.begin(), v.end(), m_Coords);
    }

    template <typename U>
    explicit Point(const Point<U, N>& other)
    {
        std::copy(other.begin(), other.end(), m_Coords);
    }

    template <typename U>
    operator Point<U, N>() const
    {
        return Point<U, N>(*this);
    }

    template <typename U>
    Point<T, N>& operator=(const Point<U, N>& other)
    {
        std::copy(other.begin(), other.end(), m_Coords);
        return *this;
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
bool operator==(const Point<T, N>& u, const Point<U, N>& v)
{
    return std::equal(u.begin(), u.end(), v.begin());
}

template <typename T, typename U, size_t N>
bool operator!=(const Point<T, N>& u, const Point<U, N>& v)
{
    return !(u == v);
}

template <typename T, typename U, size_t N>
Point<T, N>& operator+=(Point<T, N>& p, const Vector<U, N>& v)
{
    std::transform(begin(p), end(p), begin(v), begin(p),
                   [](T a, U b){return T(a + b);});
    return p;
}

template <typename T, typename U, size_t N>
Point<T, N>& operator-=(Point<T, N>& p, const Vector<U, N>& v)
{
    std::transform(begin(p), end(p), begin(v), begin(p),
                   [](T a, U b){return T(a - b);});
    return p;
}

template <typename T, typename U, size_t N>
auto operator+(const Point<T, N>& p, const Vector<U, N>& v)
    -> Point<decltype(p[0] + v[0]), N>
{
    Point<decltype(p[0] + v[0]), N> q;
    std::transform(begin(p), end(p), begin(v), begin(q),
                   [](T a, U b){return a + b;});
    return q;
}

template <typename T, typename U, size_t N>
auto operator-(const Point<T, N>& p, const Vector<U, N>& v)
    -> Point<decltype(p[0] - v[0]), N>
{
    Point<decltype(p[0] - v[0]), N> q;
    std::transform(begin(p), end(p), begin(v), begin(q),
                   [](T a, U b){return a - b;});
    return q;
}

template <typename T, typename U, size_t N>
auto operator-(const Point<T, N>& p, const Point<U, N>& q)
    -> Vector<decltype(p[0] - q[0]), N>
{
    Vector<decltype(p[0] - q[0]), N> v;
    std::transform(begin(p), end(p), begin(q), begin(v),
                   [](T a, U b){return a - b;});
    return v;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Point<T, N>& p);

template <typename T, size_t N>
const T* begin(const Point<T, N>& p)
{
    return p.begin();
}

template <typename T, size_t N>
const T* end(const Point<T, N>& p)
{
    return p.end();
}

template <typename T, size_t N>
T* begin(Point<T, N>& p)
{
    return p.begin();
}

template <typename T, size_t N>
T* end(Point<T, N>& p)
{
    return p.end();
}

template <typename T, size_t N>
Point<T, N> translate(const Point<T, N>& p, const Vector<T, N>& v);


template <typename T, typename U, size_t N>
bool equivalent(const Point<T, N>& p, const Point<U, N>& q,
                double tolerance = 1e-12);

// template <typename T, size_t N>
// bool equal(const Point<T, N>& p, const Point<T, N>& q, T tolerance = 0);

template <typename T>
T& x(Point<T, 2>& p) {return p[0];}
template <typename T>
T x(const Point<T, 2>& p) {return p[0];}
template <typename T>
void setX(Point<T, 2>& p, T x) {p[0] = x;}

template <typename T>
T& y(Point<T, 2>& p) {return p[1];}
template <typename T>
T y(const Point<T, 2>& p) {return p[1];}
template <typename T>
void setY(Point<T, 2>& p, T y) {p[1] = y;}

template <typename T>
T& x(Point<T, 3>& p) {return p[0];}
template <typename T>
T x(const Point<T, 3>& p) {return p[0];}
template <typename T>
void setX(Point<T, 3>& p, T x) {p[0] = x;}

template <typename T>
T& y(Point<T, 3>& p) {return p[1];}
template <typename T>
T y(const Point<T, 3>& p) {return p[1];}
template <typename T>
void setY(Point<T, 3>& p, T y) {p[1] = y;}

template <typename T>
T& z(Point<T, 3>& p) {return p[2];}
template <typename T>
T z(const Point<T, 3>& p) {return p[2];}
template <typename T>
void setZ(Point<T, 3>& p, T z) {p[2] = z;}

template <typename T>
void setXY(Point<T, 2>& p, T x, T y) {setX(p, x); setY(p, y);}

template <typename T>
void setXYZ(Point<T, 3>& p, T x, T y, T z) {setX(p, x); setY(p, y); setZ(p, z);}

template <typename T>
Point<T, 2> point2(T x, T y) {T c[] = {x, y}; return Point<T, 2>(c);}

template <typename T>
Point<T, 2> point2(const std::pair<T, T>& p) {T c[] = {p.first, p.second}; return Point<T, 2>(c);}

template <typename T, size_t N>
Point<T, 2> point2(const Point<T, N>& p) {return point2(x(p), y(p));}

template <typename T>
Point<T, 2> point2(const Point<T, 2>& p) {return p;}

template <typename T>
Point<T, 3> point3(T x, T y, T z) {T c[] = {x, y, z}; return Point<T, 3>(c);}

template <typename T, size_t N>
Point<T, N> point(const Vector<T, N>& v)
{
    return Point<T, N>(v);
}

template <typename T, typename U, size_t N>
Point<T, N> point(const Point<U, N>& p)
{
    return Point<T, N>(p);
}

}

#include "Point.impl.hpp"

#endif
