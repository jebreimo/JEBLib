#include <algorithm>

namespace JEBMath {

template <typename It, typename T>
void scaleValues(It first, It last, T newMin, T newMax)
{
    auto its = std::minmax_element(first, last);
    if (its.first == last)
        return;

    auto curMin = *its.first;
    auto curMax = *its.second;
    auto curRange = curMax - curMin;

    auto newRange = newMax - newMin;

    for (auto it = first; it != last; ++it)
        *it = newMin + (*it - curMin) * newRange / curRange;
}

}
