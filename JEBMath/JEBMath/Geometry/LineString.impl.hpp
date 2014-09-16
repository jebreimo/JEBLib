#include <cassert>
#include <ostream>

namespace JEBMath {

template <typename T, size_t N>
size_t segmentCount(const std::vector<Point<T, N>>& lineString)
{
    return lineString.empty() ? 0 : lineString.size() - 1;
}

template <typename T, size_t N>
LineSegment<T, N> segment(const std::vector<Point<T, N>>& lineString, size_t i)
{
    assert(i < segmentCount(lineString));
    return LineSegment<T, N>(lineString[i], lineString[i + 1]);
}

template <typename T, size_t N>
LineSegment<T, N> firstSegment(const std::vector<Point<T, N>>& lineString)
{
    return segment(lineString, 0);
}

template <typename T, size_t N>
LineSegment<T, N> lastSegment(const std::vector<Point<T, N>>& lineString)
{
    assert(segmentCount(lineString) != 0);
    return segment(lineString, lineString.size() - 2);
}

template <typename T, size_t N>
void removeSegment(std::vector<Point<T, N>>& lineString, size_t i)
{
    lineString.erase(lineString.begin() + i, lineString.begin() + i + 1);
}

template <typename T, size_t N>
std::pair<Point<T, N>, Point<T, N>> boundingBox(
        const std::vector<Point<T, N>>& lineString)
{
    if (lineString.empty())
        return std::pair<Point<T, N>, Point<T, N>>();
    auto it = begin(lineString);
    auto min = *it, max = *it;
    for (++it; it != end(lineString); ++it)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if ((*it)[i] < min[i])
                min[i] = (*it)[i];
            else if (max[i] < (*it)[i])
                max[i] = (*it)[i];
        }
    }
    return std::make_pair(min, max);
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const std::vector<Point<T, N>>& ls)
{
    if (ls.empty())
        return os;
    auto it = ls.begin();
    os << "[" << *it;
    for (it++; it != ls.end(); ++it)
        os << " " << *it;
    os << "]";
    return os;
}

}
