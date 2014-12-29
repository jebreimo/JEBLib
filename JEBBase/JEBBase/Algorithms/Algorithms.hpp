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
#include "AlgorithmsCpp14.hpp"

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

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> searchLastImpl(FwdIt1 beg, FwdIt1 end,
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
std::pair<BiIt, BiIt> searchLastImpl(BiIt beg, BiIt end,
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
std::pair<FwdIt1, FwdIt1> searchLast(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                      BinaryPredicate pred)
{
    return searchLastImpl(
            beg, end,
            cmpBeg, cmpEnd,
            pred,
            typename std::iterator_traits<FwdIt1>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> searchLast(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    return searchLast(
            beg, end,
            cmpBeg, cmpEnd,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type
                         >());
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> searchNthLast(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count,
                                          BinaryPredicate pred)
{
    std::pair<FwdIt1, FwdIt1> its = std::make_pair(end, end);
    for (size_t i = 0; i < count; i++)
    {
        its = searchLast(beg, its.first, cmpBeg, cmpEnd, pred);
        if (its.first == its.second)
        {
            its = std::make_pair(end, end);
            break;
        }
    }
    return its;
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> searchNthLast(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count)
{
    return searchNthLast(
            beg, end,
            cmpBeg, cmpEnd,
            count,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type
                         >());
}

template <typename FwdIt, typename Value>
FwdIt findLastImpl(FwdIt beg, FwdIt end,
                        const Value& value,
                        std::forward_iterator_tag)
{
    FwdIt it = end;
    while (beg != end)
    {
        if (*beg == value)
            it = beg;
        ++beg;
    }
    return it;
}

template <typename BiIt, typename Value>
BiIt findLastImpl(BiIt beg, BiIt end,
                    const Value& value,
                    std::bidirectional_iterator_tag)
{
    BiIt it = end;
    while (beg != it)
    {
        --it;
        if (*it == value)
            break;
    }
    return it;
}

template <typename FwdIt, typename Value>
FwdIt findLast(FwdIt beg, FwdIt end, const Value& value)
{
    return findLastImpl(
            beg, end, value,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findLastIfImpl(FwdIt beg, FwdIt end,
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
BiIt findLastIfImpl(BiIt beg, BiIt end,
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
FwdIt findLastIf(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return findLastIfImpl(
            beg, end, predicate,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt findLastIfNot(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return findLastIf(beg, end,
                        [&](decltype(*beg) s){return !predicate(s);});
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findEndIfImpl(FwdIt beg, FwdIt end,
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
BiIt findEndIfImpl(BiIt beg, BiIt end,
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
FwdIt findEndIf(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return findEndIfImpl(
            beg, end, predicate,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt, typename UnaryPredicate>
FwdIt findEndIfNot(FwdIt beg, FwdIt end, UnaryPredicate predicate)
{
    return findEndIf(beg, end,
                       [&](decltype(*beg) s){return !predicate(s);});
}

template <typename FwdIt1, typename FwdIt2>
FwdIt1 findLastOf(FwdIt1 first, FwdIt1 last,
                  FwdIt2 firstValue, FwdIt2 lastValue)
{
    return findLastIf(
            first, last,
            [&](decltype(*first) s)
               {return std::find(firstValue, lastValue, s) != lastValue;});
}

template <typename RndIt, typename T>
RndIt binaryFind(RndIt beg, RndIt end, const T& value)
{
    RndIt it = std::lower_bound(beg, end, value);
    if (it == end || value < *it)
      return end;
    return it;
}

template <typename InIt, typename OutIt, typename UnaryPred,
          typename UnaryFunc>
OutIt transformIf(InIt first, InIt last, OutIt dst,
                  UnaryPred predicate, UnaryFunc tranFunc)
{
    for (; first != last; ++first)
    {
        if (predicate(*first))
        {
            *dst = tranFunc(*first);
            ++dst;
        }
    }
    return dst;
}

}}

#endif
