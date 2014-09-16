#include "Point.hpp"

#include <functional>
#include "JEBMath/Math/Utilities.hpp"

namespace JEBMath {

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v)
{
    const T* it = v.begin();
    os << "[" << *it;
    while (++it != v.end())
        os << " " << *it;
    return os << "]";
}

template <typename T, size_t N>
T lengthSquared(const Vector<T, N>& v)
{
    return v * v;
}

template <typename T, size_t N>
double length(const Vector<T, N>& v)
{
    return std::sqrt(lengthSquared(v));
}

template <typename T, size_t N>
Vector<double, N> unit(const Vector<T, N>& v)
{
    return v / length(v);
}

template <typename T, size_t N>
double cosAngle(const Vector<T, N>& u, const Vector<T, N>& v)
{
    return u * v / std::sqrt(lengthSquared(u) * lengthSquared(v));
}

template <typename T, typename U, size_t N>
double angle(const Vector<T, N>& u, const Vector<U, N>& v)
{
    return std::acos(cosAngle(u, v));
}

template <typename T, typename U, size_t N>
bool equivalent(const Vector<T, N>& u, const Vector<U, N>& v, double epsilon)
{
    return lengthSquared(u - v) <= epsilon * epsilon;
}

template <typename T>
Vector<T, 2> normal(const Vector<T, 2>& v)
{
    return vector2(-y(v), x(v));
}

template <typename T>
Vector<double, 2> rotate(const Vector<T, 2>& v, double radians)
{
    auto c = std::cos(radians);
    auto s = std::sin(radians);
    return vector2(x(v) * c - y(v) * s, x(v) * s + y(v) * c);
}

}
