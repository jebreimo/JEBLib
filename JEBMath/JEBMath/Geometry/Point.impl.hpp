#include <cmath>
#include <functional>
#include <ostream>
#include "Vector.hpp"

namespace JEBMath {

// template <typename U, typename T, size_t N>
// Point<T, N>::Point(const Vector<U, N>& v)
// {
//     std::copy(begin(v), end(v), m_Coords);
// }

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Point<T, N>& p)
{
    const T* it = p.begin();
    os << "[" << *it;
    while (++it != p.end())
        os << " " << *it;
    return os << "]";
}

template <typename T, size_t N>
Point<T, N> translate(const Point<T, N>& p, const Vector<T, N>& v)
{
    Point<T, N> r;
    std::transform(p.begin(), p.end(), v.begin(), r.begin(), std::plus<T>());
    return r;
}

// template <typename T, size_t N>
// bool equal(const Point<T, N>& p, const Point<T, N>& q, T tolerance)
// {
//     for (size_t i = 0; i != N; ++i)
//     {
//         if (std::abs(p[i] - q[i]) > tolerance)
//             return false;
//     }
//     return true;
// }

template <typename T, typename U, size_t N>
bool equivalent(const Point<T, N>& p, const Point<U, N>& q, double tolerance)
{
    return lengthSquared(q - p) <= tolerance * tolerance;
}

}
