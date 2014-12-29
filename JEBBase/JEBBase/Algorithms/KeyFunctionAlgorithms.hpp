/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_ALGORITHMS_KEYFUNCTIONALGORITHMS_HPP
#define JEBBASE_ALGORITHMS_KEYFUNCTIONALGORITHMS_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include "Algorithms.hpp"

/** @file
  * @brief Defines various wrappers and extensions to the generic algorithms
  *     in the standard library's algorithm header.
  */

namespace JEBBase
{
/** @brief The namespace for generic algorithms.
  */
namespace Algorithms
{

template <typename RndIt, typename T, typename UnaryFunc>
RndIt lowerBound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (keyFunc(*mid) < value)
            beg = mid + 1;
        else
            end = mid;
    }
    return beg;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt upperBound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (value < keyFunc(*mid))
            end = mid;
        else
            beg = mid + 1;
    }
    return beg;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt binaryFind(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = Algorithms::lowerBound(beg, end, value, keyFunc);
    if (it == end || value < keyFunc(*it))
      return end;
    return it;
}

template <typename RndIt, typename T, typename UnaryFunc>
bool binarySearch(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = Algorithms::lowerBound(beg, end, value, keyFunc);
    return it != end && value == keyFunc(*it);
}

template <typename RndIt, typename T, typename UnaryFunc>
std::pair<RndIt, RndIt> bounds(
        RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt first = ::JEBBase::Algorithms::lowerBound(
            beg, end, value, keyFunc);
    RndIt second = ::JEBBase::Algorithms::upperBound(
            first, end, value, keyFunc);
    return std::make_pair(first, second);
}

template <typename UnaryFunc>
class KeyComparer
{
public:
    KeyComparer(UnaryFunc keyFunc) : m_KeyFunc(keyFunc) {}
    template <typename T>
    bool operator()(T a, T b) {return m_KeyFunc(a) < m_KeyFunc(b);}
private:
    UnaryFunc m_KeyFunc;
};

template <typename RndIt, typename UnaryFunc>
void sortByKey(RndIt beg, RndIt end, UnaryFunc keyFunc)
{
    std::sort(beg, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt maxElementByKey(FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::max_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt minElementByKey(FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::min_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
std::pair<FwdIt, FwdIt> minmaxElementByKey(
        FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::minmax_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

}}

#endif
