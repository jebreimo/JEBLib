#include <cstdlib>
#include "JEBMath/Math/Comparisons.hpp"

namespace JEBMath { namespace Dim2 {

template <typename T>
class DirectionComparer2
{
public:
    DirectionComparer2(const Point<T, 2>& center, T tolerance = 0)
        : m_Center(center),
          m_Tolerance(tolerance)
    {
    }

    template <typename Point>
    int compare(const Point& a, const Point& b) const
    {
        T xa = x(a) - x(m_Center);
        T xb = x(b) - x(m_Center);
        T ya = y(a) - y(m_Center);
        T yb = y(b) - y(m_Center);

        if (less(xa * xb, T(0), m_Tolerance))
            return xa > xb ? -1 : 1;
        else if (equal(xa * xb, T(0), m_Tolerance) &&
                 less(ya * yb, T(0), m_Tolerance))
            return ya > yb ? -1 : 1;

        T det = ya * xb - xa * yb;
        if (equal(det, T(0), m_Tolerance))
            return 0;
        else
            return det > 0 ? -1 : 1;
    }

    template <typename Point>
    bool operator()(const Point& a, const Point& b) const
    {
        T xa = x(a) - x(m_Center);
        T xb = x(b) - x(m_Center);
        T xproduct = xa * xb;
        if (xproduct < 0)
            return xa > xb;

        T ya = y(a) - y(m_Center);
        T yb = y(b) - y(m_Center);

        if (xproduct == 0 && ya * yb < 0)
            return ya > yb;

        T det = ya * xb - xa * yb;
        if (det != 0)
            return det > 0;
        else
            return xa * xa + ya * ya > xb * xb + yb * yb;
    }
private:
    Point<T, 2> m_Center;
    T m_Tolerance;
};

template <typename T>
bool areTangentialAtPoint(const Point<T, 2>& point,
                          Point<T, 2> fromA, Point<T, 2> toA,
                          Point<T, 2> fromB, Point<T, 2> toB,
                          double tolerance)
{
    DirectionComparer2<T> comparer(point, tolerance);
    if (!comparer(fromA, toA))
      std::swap(fromA, toA);
    if (!comparer(fromB, toB))
      std::swap(fromB, toB);

    if (comparer.compare(toA, fromB) <= 0)
      return true;
    else if (comparer.compare(fromA, toB) >= 0)
      return true;
    else
      return std::abs(comparer.compare(fromA, fromB) +
                      comparer.compare(toA, toB)) != 2;
}

template <typename BiIt>
BiIt findIntersection(LineSegmentD lineSeg,
                      BiIt firstPoint, BiIt lastPoint,
                      double epsilon)
{
    for (BiIt it = firstPoint; it != lastPoint; ++it)
    {
        if (intersects(lineSeg, LineSegmentD(*it, *std::next(it)), epsilon))
            return it;
    }
    return lastPoint;
}

template <typename T>
Side::Enum side(const Line<T, 2>& l, const Point<T, 2>& p)
{
    double tmp = (double)dot(normal(l.vector()), Vector<T, 2>(l.point(), p));
    if (tmp > 0)
      return Side::Left;
    else if (tmp < 0)
      return Side::Right;
    else
      return Side::Neither;
}

}}
