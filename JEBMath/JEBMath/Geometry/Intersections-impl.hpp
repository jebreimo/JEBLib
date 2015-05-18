#include <cstdlib>
#include "../Math/Comparisons.hpp"

namespace JEBMath {

template <typename T>
class DirectionComparer2
{
public:
    DirectionComparer2(const Vector<T, 2>& center, T tolerance = 0)
        : m_Center(center),
          m_Tolerance(tolerance)
    {
    }

    template <typename Point>
    int compare(const Point& a, const Point& b) const
    {
        T xa = getX(a) - getX(m_Center);
        T xb = getX(b) - getX(m_Center);
        T ya = getY(a) - getY(m_Center);
        T yb = getY(b) - getY(m_Center);

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
        T xa = getX(a) - getX(m_Center);
        T xb = getX(b) - getX(m_Center);
        T xproduct = xa * xb;
        if (xproduct < 0)
            return xa > xb;

        T ya = getY(a) - getY(m_Center);
        T yb = getY(b) - getY(m_Center);

        if (xproduct == 0 && ya * yb < 0)
            return ya > yb;

        T det = ya * xb - xa * yb;
        if (det != 0)
            return det > 0;
        else
            return xa * xa + ya * ya > xb * xb + yb * yb;
    }
private:
    Vector<T, 2> m_Center;
    T m_Tolerance;
};

template <typename T>
bool areTangentialAtPoint(const Vector<T, 2>& point,
                          Vector<T, 2> fromA, Vector<T, 2> toA,
                          Vector<T, 2> fromB, Vector<T, 2> toB,
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
BiIt findIntersection(LineSegment<double, 2> lineSeg,
                      BiIt firstPoint, BiIt lastPoint,
                      double epsilon)
{
    for (BiIt it = firstPoint; it != lastPoint; ++it)
    {
        if (intersects(lineSeg, LineSegment<double, 2>(*it, *std::next(it)), epsilon))
            return it;
    }
    return lastPoint;
}

template <typename T>
Side::Enum getide(const Line<T, 2>& l, const Vector<T, 2>& p)
{
    auto tmp = getNormal(l.getVector()) * (p - l.getPoint());
    if (tmp > 0)
      return Side::Left;
    else if (tmp < 0)
      return Side::Right;
    else
      return Side::Neither;
}

}
