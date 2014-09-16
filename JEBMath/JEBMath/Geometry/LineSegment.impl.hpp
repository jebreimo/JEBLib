namespace JEBMath {

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const LineSegment<T, N>& ls)
{
    return os << "[start | " << ls.start() << " | end | " << ls.end() << "]";
}

template <typename T, size_t N>
LineSegment<T, N> lineSegment(const Point<T, N>& start, const Point<T, N>& end)
{
    return LineSegment<T, N>(start, end);
}

template <typename T, size_t N>
LineSegment<T, N> reverse(const LineSegment<T, N>& seg)
{
    return LineSegment<T, N>(seg.end(), seg.start());
}

template <typename T, size_t N>
double length(const LineSegment<T, N>& ls)
{
    return length(ls.vector());
}

template <typename T, size_t N>
Point<T, N> nearestPoint(const LineSegment<T, N>& ls, const Point<T, N>& p)
{
    double divisor = lengthSquared(ls.vector());
    double t = (p - ls.start()) * ls.vector() / divisor;
    if (t <= 0)
        return ls.start();
    else if (t >= 1)
        return ls.end();
    else
        return ls.pointAtT(t);
}

template <typename T>
Point<T, 2> relativePosition(const LineSegment<T, 2>& ls, const Point<T, 2>& p)
{
    Vector<T, 2> lv = ls.vector();
    Vector<T, 2> pv = p - ls.start();
    double len = lengthSquared(lv);
    return point2(lv * pv / len, normal(lv) * pv / len);
}

}
