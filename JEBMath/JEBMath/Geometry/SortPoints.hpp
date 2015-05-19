#include <algorithm>
#include <vector>
#include "Vector.hpp"

namespace JEBMath {

template <typename T>
class DirectionComparer
{
public:
    DirectionComparer(const Vector<T, 2>& center)
        : m_Center(center)
    {
    }

    template <unsigned N>
    bool operator()(const Vector<T, N>& a, const Vector<T, N>& b) const
    {
        T ya = getY(a) - getY(m_Center);
        T yb = getY(b) - getY(m_Center);
        T yproduct = ya * yb;
        if (yproduct < 0)
            return ya > 0;

        T xa = getX(a) - getX(m_Center);
        T xb = getX(b) - getX(m_Center);

        if (yproduct == 0)
        {
            if (ya != yb)
            {
              if (yb != 0 && xa > 0)
                  return true;
              else if (ya != 0 && xb > 0)
                  return false;
            }
            else
            {
                if (xa * xb < 0)
                    return xa > 0;
                else
                    return fabs(xa) > fabs(xb);
            }
        }

        double det = -ya * xb + xa * yb;
        if (det != 0)
            return det > 0;
        else
            return xa * xa + ya * ya > xb * xb + yb * yb;
    }
private:
    Vector<T, 2> m_Center;
};

template <typename RndIt, typename T>
void sortClockwise(RndIt begin, RndIt end, const Vector<T, 2>& center)
{
    std::sort(begin, end, DirectionComparer<T>(center));
}

template <typename RndIt, typename T, typename UnaryFunc>
void sortClockwise(RndIt begin, RndIt end,
                   const Vector<T, 2>& center,
                   UnaryFunc getPoint)
{
    DirectionComparer<T> dircmp(center);
    auto cmp = [&getPoint, &dircmp]
                (const typename std::iterator_traits<RndIt>::value_type& a,
                 const typename std::iterator_traits<RndIt>::value_type& b)
                {
                    return dircmp(getPoint(a), getPoint(b));
                };
    std::sort(begin, end, cmp);
}

template <typename T>
void sortClockwise(std::vector<Vector<T, 2>>& points,
                   const Vector<T, 2>& center)
{
    sortClockwise(points.begin(), points.end(), center);
}

template <unsigned N>
struct NthIsLess
{
    template <typename Point>
    bool operator()(const Point& a, const Point& b)
    {
        return a[N] < b[N] || (a[N] == b[N] && a[1 - N] < b[1 - N]);
    }
};

template <unsigned M, unsigned N, typename RndIt>
void sortImpl(RndIt beg, RndIt end)
{
    if (beg == end)
        return;
    RndIt mid = beg + std::distance(beg, end) / 2;
    nth_element(beg, mid, end, NthIsLess<M>());
    sortImpl<N, M>(beg, mid);
    sortImpl<N, M>(mid + 1, end);
}

/** @brief Sorts the points in-place in the same order they would be arranged
  *     in a XY-tree.
  *
  * The algorithm has O(n log(n)) time consumption
  */
template <typename RndIt>
void sortPointsXY(RndIt beg, RndIt end)
{
    sortImpl<0, 1>(beg, end);
}

template <typename RndIt>
void sortPointsXZ(RndIt beg, RndIt end)
{
    sortImpl<0, 2>(beg, end);
}

template <typename RndIt>
void sortPointsYZ(RndIt beg, RndIt end)
{
    sortImpl<1, 2>(beg, end);
}

}
