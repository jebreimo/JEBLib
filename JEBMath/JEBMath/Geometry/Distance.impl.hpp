#include "Vector.hpp"

namespace JEBMath {

template <typename T, typename U, size_t N>
double distance(const Point<T, N>& a, const Point<U, N>& b)
{
    return length(b - a);
}

template <typename T, typename U>
double distance(const Line<T, 2>& l, const Point<U, 2>& p)
{
    auto v = p - l.point();
    return normal(l.vector()) * v / length(l.vector());
}

template <typename T, typename U>
double distance(const Point<T, 2>& p, const Line<U, 2>& l)
{
    return distance(l, p);
}

template <typename T, typename U>
double distance(const LineSegment<T, 2>& ls, const Point<U, 2>& p)
{
    auto v = p - ls.start();
    double t = ls.vector() * v / lengthSquared(ls.vector());
    if (t <= 0)
        return length(v);
    else if (t >= 1)
        return length(p - ls.end());
    else
        return normal(ls.vector()) * v / length(ls);
}

template <typename T, typename U>
double distance(const Point<T, 2>& p, const LineSegment<U, 2>& ls)
{
    return distance(ls, p);
}

}
