#include "Vector.hpp"

namespace JEBMath {

template <typename T, typename U, unsigned N>
double getDistance(const Vector<T, N>& a, const Vector<U, N>& b)
{
    return getLength(b - a);
}

template <typename T, typename U>
double getDistance(const Line<T, 2>& l, const Vector<U, 2>& p)
{
    auto v = p - l.getPoint();
    return getNormal(l.getVector()) * v / getLength(l.getVector());
}

template <typename T, typename U>
double getDistance(const Vector<T, 2>& p, const Line<U, 2>& l)
{
    return getDistance(l, p);
}

template <typename T, typename U>
double getDistance(const LineSegment<T, 2>& ls, const Vector<U, 2>& p)
{
    auto v = p - ls.getStart();
    auto t = ls.getVector() * v / getLengthSquared(ls.getVector());
    if (t <= 0)
        return getLength(v);
    else if (t >= 1)
        return getLength(p - ls.getEnd());
    else
        return getNormal(ls.getVector()) * v / getLength(ls);
}

template <typename T, typename U>
double getDistance(const Vector<T, 2>& p, const LineSegment<U, 2>& ls)
{
    return getDistance(ls, p);
}

}
