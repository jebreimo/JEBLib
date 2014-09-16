/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_ALGORITHMS_ALGORITHMS_HPP
#define JEBBASE_ALGORITHMS_ALGORITHMS_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include "JEBBase/JEBBaseDefinitions.hpp"

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

template <typename InpIt1, typename InpIt2>
std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                   InpIt2 cmpBeg, InpIt2 cmpEnd)
{
    while (beg != end && cmpBeg != cmpEnd && *beg == *cmpBeg)
    {
        beg++;
        cmpBeg++;
    }
    return std::make_pair(beg, cmpBeg);
}

template <typename InpIt1, typename InpIt2, typename BinaryPredicate>
std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                   InpIt2 cmpBeg, InpIt2 cmpEnd,
                                   BinaryPredicate pred)
{
    while (beg != end && cmpBeg != cmpEnd && pred(*beg, *cmpBeg))
    {
        beg++;
        cmpBeg++;
    }
    return std::make_pair(beg, cmpBeg);
}

template <typename InpIt1, typename InpIt2, typename BinaryFunc>
auto compare(InpIt1 first, InpIt1 last,
             InpIt2 cmpFirst, InpIt2 cmpLast)
    -> decltype(*first - *cmpFirst)
{
    typedef decltype(*first - *cmpFirst) ReturnType;
    auto its = Algorithms::mismatch(first, last, cmpFirst, cmpLast);
    if (its.first != last && its.second != cmpLast)
        return *first - *cmpFirst;
    else if (its.first != last)
        return ReturnType(1);
    else if (its.second != cmpLast)
        return ReturnType(-1);
    else
        return ReturnType();
}

template <typename InpIt1, typename InpIt2, typename BinaryFunc>
auto compare(InpIt1 first, InpIt1 last,
             InpIt2 cmpFirst, InpIt2 cmpLast,
             BinaryFunc cmp)
    -> decltype(cmp(*first, *cmpFirst))
{
    typedef decltype(*first - *cmpFirst) ReturnType;
    auto its = Algorithms::mismatch(first, last, cmpFirst, cmpLast,
            [&](decltype(*first) a, decltype(*cmpFirst) b)
                {return cmp(a, b) == 0;});
    if (its.first != last && its.second != cmpLast)
        return cmp(*its.first, *its.second);
    else if (its.first != last)
        return ReturnType(1);
    else if (its.second != cmpLast)
        return ReturnType(-1);
    else
        return ReturnType();
}

template <typename FwdIt1, typename FwdIt2>
bool equal(FwdIt1 beg, FwdIt1 end,
           FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    return Algorithms::mismatch(beg, end, cmpBeg, cmpEnd) ==
            std::make_pair(end, cmpEnd);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
bool equal(FwdIt1 beg, FwdIt1 end,
           FwdIt2 cmpBeg, FwdIt2 cmpEnd,
           BinaryPredicate pred)
{
    return Algorithms::mismatch(beg, end, cmpBeg, cmpEnd, pred) ==
            std::make_pair(end, cmpEnd);
}

template <typename FwdIt1, typename FwdIt2>
bool less(FwdIt1 first, FwdIt1 last,
          FwdIt2 cmpFirst, FwdIt2 cmpLast)
{
    auto its = Algorithms::mismatch(first, last, cmpFirst, cmpLast);
    if (its.first != last && its.second != cmpLast)
        return *its.first < *its.second;
    else
        return its.first == last && its.second != cmpLast;
}

template <typename FwdIt1, typename FwdIt2,
          typename BinaryPredicate1, typename BinaryPredicate2>
bool less(FwdIt1 first, FwdIt1 last,
          FwdIt2 cmpFirst, FwdIt2 cmpLast,
          BinaryPredicate1 isEqual,
          BinaryPredicate2 isLess)
{
    auto its = Algorithms::mismatch(first, last, cmpFirst, cmpLast, isEqual);
    if (its.first != last && its.second != cmpLast)
        return isLess(*its.first, *its.second);
    else
        return its.first == last && its.second != cmpLast;
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search(FwdIt1 beg, FwdIt1 end,
                                 FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    while (beg != end)
    {
        auto its = Algorithms::mismatch(beg, end, cmpBeg, cmpEnd);
        if (its.second == cmpEnd)
            return std::make_pair(beg, its.first);
        else if (its.first == end)
            break;
        beg++;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search(FwdIt1 beg, FwdIt1 end,
                                 FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                 BinaryPredicate pred)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    while (beg != end)
    {
        auto its = Algorithms::mismatch(beg, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            return std::make_pair(beg, its.first);
        else if (its.first == end)
            break;
        beg++;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_last_impl(FwdIt1 beg, FwdIt1 end,
                                           FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                           BinaryPredicate pred,
                                           std::forward_iterator_tag)
{
    std::pair<FwdIt1, FwdIt1> result(end, end);
    if (cmpBeg == cmpEnd)
        return result;
    while (beg != end)
    {
        auto its = Algorithms::mismatch(beg, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            result = std::make_pair(beg, its.first);
        beg++;
    }
    return result;
}

template <typename BiIt, typename FwdIt, typename BinaryPredicate>
std::pair<BiIt, BiIt> search_last_impl(BiIt beg, BiIt end,
                                       FwdIt cmpBeg, FwdIt cmpEnd,
                                       BinaryPredicate pred,
                                       std::bidirectional_iterator_tag)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    BiIt it = end;
    while (it != beg)
    {
        --it;
        auto its = Algorithms::mismatch(it, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            return std::make_pair(it, its.first);
    }
    return std::make_pair(it, it);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_last(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                      BinaryPredicate pred)
{
    return search_last_impl(
            beg, end,
            cmpBeg, cmpEnd,
            pred,
            typename std::iterator_traits<FwdIt1>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search_last(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    return search_last(
            beg, end,
            cmpBeg, cmpEnd,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type
                         >());
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_nth_last(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count,
                                          BinaryPredicate pred)
{
    std::pair<FwdIt1, FwdIt1> its = std::make_pair(end, end);
    for (size_t i = 0; i < count; i++)
    {
        its = search_last(beg, its.first, cmpBeg, cmpEnd, pred);
        if (its.first == its.second)
        {
            its = std::make_pair(end, end);
            break;
        }
    }
    return its;
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search_nth_last(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count)
{
    return search_nth_last(
            beg, end,
            cmpBeg, cmpEnd,
            count,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type
                         >());
}

template <typename FwdIt, typename UnaryFunc>
FwdIt find_last_if_impl(FwdIt beg, FwdIt end,
                        UnaryFunc predicate,
                        std::forward_iterator_tag)
{
    FwdIt it = end;
    while (beg != end)
    {
        if (predicate(*beg))
            it = beg;
        ++beg;
    }
    return it;
}

template <typename BiIt, typename UnaryPredicate>
BiIt find_last_if_impl(BiIt beg, BiIt end,
                       UnaryPredicate predicate,
                       std::bidirectional_iterator_tag)
{
    BiIt it = end;
    while (beg != it)
    {
        --it;
        if (predicate(*it))
            break;
    }
    return it;
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt find_last_if(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return find_last_if_impl(
            beg, end,
            predicate,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt find_last_if_not(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return find_last_if(beg, end,
                        [&](decltype(*beg) s){return !predicate(s);});
}

template <typename FwdIt, typename UnaryFunc>
FwdIt find_end_if_impl(FwdIt beg, FwdIt end,
                       UnaryFunc predicate,
                       std::forward_iterator_tag)
{
    FwdIt it = end;
    while (beg != end)
    {
        if (predicate(*beg))
            it = ++beg;
        else
            ++beg;
    }
    return it;
}

template <typename BiIt, typename UnaryPredicate>
BiIt find_end_if_impl(BiIt beg, BiIt end,
                      UnaryPredicate predicate,
                      std::bidirectional_iterator_tag)
{
    BiIt it = end;
    while (beg != it)
    {
        --it;
        if (predicate(*it))
            return ++it;
    }
    return it;
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt find_end_if(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return find_end_if_impl(
            beg, end,
            predicate,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt find_end_if_not(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return find_end_if(beg, end,
                       [&](decltype(*beg) s){return !predicate(s);});
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt lower_bound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
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
RndIt upper_bound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
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
RndIt binary_find(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = Algorithms::lower_bound(beg, end, value, keyFunc);
    if (it == end || value < keyFunc(*it))
      return end;
    return it;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt binary_find(RndIt beg, RndIt end, const T& value)
{
    RndIt it = std::lower_bound(beg, end, value);
    if (it == end || value < *it)
      return end;
    return it;
}

template <typename RndIt, typename T, typename UnaryFunc>
bool binary_search(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = Algorithms::lower_bound(beg, end, value, keyFunc);
    return it != end && value == keyFunc(*it);
}

template <typename RndIt, typename T, typename UnaryFunc>
std::pair<RndIt, RndIt> bounds(
        RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt first = ::JEBBase::Algorithms::lower_bound(
            beg, end, value, keyFunc);
    RndIt second = ::JEBBase::Algorithms::upper_bound(
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
void sort_by_key(RndIt beg, RndIt end, UnaryFunc keyFunc)
{
    std::sort(beg, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt max_element_by_key(FwdIt begin, FwdIt end, UnaryFunc func)
{
    return std::max_element(begin, end, KeyComparer<UnaryFunc>(func));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt min_element_by_key(FwdIt begin, FwdIt end, UnaryFunc func)
{
    return std::min_element(begin, end, KeyComparer<UnaryFunc>(func));
}

template <typename FwdIt, typename UnaryFunc>
std::pair<FwdIt, FwdIt> minmax_element_by_key(
        FwdIt begin, FwdIt end, UnaryFunc func)
{
    return std::minmax_element(begin, end, KeyComparer<UnaryFunc>(func));
}

template <typename InIt, typename OutIt, typename UnaryPred,
          typename UnaryFunc>
OutIt transform_if(InIt first, InIt last, OutIt dst,
                   UnaryPred predicate, UnaryFunc func)
{
    for (; first != last; ++first)
    {
        if (predicate(*first))
        {
            *dst = func(*first);
            ++dst;
        }
    }
    return dst;
}

}}

#endif
