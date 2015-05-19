#include <cassert>
#include <ostream>

namespace JEBMath {

template <typename T, unsigned N>
size_t getSegmentCount(const std::vector<Vector<T, N>>& lineString)
{
    return lineString.empty() ? 0 : lineString.size() - 1;
}

template <typename T, unsigned N>
LineSegment<T, N> getSegment(const std::vector<Vector<T, N>>& lineString,
                             size_t i)
{
    assert(i < getSegmentCount(lineString));
    return LineSegment<T, N>(lineString[i], lineString[i + 1]);
}

template <typename T, unsigned N>
LineSegment<T, N> getFirstSegment(const std::vector<Vector<T, N>>& lineString)
{
    return getSegment(lineString, 0);
}

template <typename T, unsigned N>
LineSegment<T, N> getLastSegment(const std::vector<Vector<T, N>>& lineString)
{
    assert(getSegmentCount(lineString) != 0);
    return getSegment(lineString, lineString.size() - 2);
}

template <typename T, unsigned N>
void removeSegment(std::vector<Vector<T, N>>& lineString, size_t i)
{
    lineString.erase(lineString.begin() + i, lineString.begin() + i + 1);
}

template <typename T, unsigned N>
std::pair<Vector<T, N>, Vector<T, N>> getBoundingBox(
        const std::vector<Vector<T, N>>& lineString)
{
    if (lineString.empty())
        return std::pair<Vector<T, N>, Vector<T, N>>();
    auto it = begin(lineString);
    auto min = *it, max = *it;
    for (++it; it != end(lineString); ++it)
    {
        for (unsigned i = 0; i < N; ++i)
        {
            if ((*it)[i] < min[i])
                min[i] = (*it)[i];
            else if (max[i] < (*it)[i])
                max[i] = (*it)[i];
        }
    }
    return std::make_pair(min, max);
}

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const std::vector<Vector<T, N>>& ls)
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
