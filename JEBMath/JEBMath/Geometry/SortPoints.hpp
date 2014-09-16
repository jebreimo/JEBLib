#include <algorithm>
#include <vector>
#include "Point.hpp"

namespace JEBMath { namespace Dim2 {

template <typename T>
class DirectionComparer
{
public:
    DirectionComparer(const Point<T, 2>& center)
        : m_Center(center)
    {
    }

    template <typename Point>
    bool operator()(const Point& a, const Point& b) const
    {
        T ya = y(a) - y(m_Center);
        T yb = y(b) - y(m_Center);
        T yproduct = ya * yb;
        if (yproduct < 0)
            return ya > 0;

        T xa = x(a) - x(m_Center);
        T xb = x(b) - x(m_Center);

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
    Point<T, 2> m_Center;
};

template <typename RndIt, typename T>
void sortClockwise(RndIt begin, RndIt end, const Point<T, 2>& center)
{
    std::sort(begin, end, DirectionComparer<T>(center));
}

template <typename RndIt, typename T, typename UnaryFunc>
void sortClockwise(RndIt begin, RndIt end,
                   const Point<T, 2>& center,
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
void sortClockwise(std::vector<Point<T, 2>>& points, const Point<T, 2>& center)
{
    sortClockwise(points.begin(), points.end(), center);
}

template <int N>
struct NthIsLess
{
    template <typename Point>
    bool operator()(const Point& a, const Point& b)
    {
        return a[N] < b[N] || (a[N] == b[N] && a[1 - N] < b[1 - N]);
    }
};

template <int N, typename RndIt>
void sortImpl(RndIt beg, RndIt end)
{
    if (beg == end)
        return;
    RndIt mid = beg + std::distance(beg, end) / 2;
    nth_element(beg, mid, end, NthIsLess<N>());
    sortImpl<1 - N>(beg, mid);
    sortImpl<1 - N>(mid + 1, end);
}

/** @brief Sorts the points in-place in the same order they would be arranged
  *     in a XY-tree.
  *
  * The algorithm has O(n log(n)) time consumption
  */
template <typename RndIt>
void sort(RndIt beg, RndIt end)
{
    sortImpl<0>(beg, end);
}

}}
