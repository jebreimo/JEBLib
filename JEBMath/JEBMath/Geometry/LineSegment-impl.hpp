#include "../Math/Utilities.hpp"

namespace JEBMath {

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const LineSegment<T, N>& line)
{
    return os << "{\"start\": " << line.getStart()
              << ", \"end\": " << line.getEnd() << "}";
}

template <typename T, unsigned N>
LineSegment<T, N> makeLineSegment(const Vector<T, N>& start,
                                  const Vector<T, N>& end)
{
    return LineSegment<T, N>(start, end);
}

template <typename T, unsigned N>
LineSegment<T, N> getReverse(const LineSegment<T, N>& line)
{
    return LineSegment<T, N>(line.getEnd(), line.getStart());
}

template <typename T, unsigned N>
double getLength(const LineSegment<T, N>& line)
{
    return getLength(line.getVector());
}

template <typename T, unsigned N>
Vector<T, N> getNearestPoint(const LineSegment<T, N>& line,
                             const Vector<T, N>& point)
{
    double divisor = getLengthSquared(line.getVector());
    double t = (point - line.getStart()) * line.getVector() / divisor;
    return line.getPointAtT(getClamped(t, 0.0, 1.0));
}

template <typename T>
Vector<T, 2> getRelativePosition(const LineSegment<T, 2>& line,
                                 const Vector<T, 2>& point)
{
    auto lv = line.getVector();
    double len = getLengthSquared(lv);
    auto pv = point - line.getStart();
    return vector2<T>(lv * pv / len, getNormal(lv) * pv / len);
}

}
