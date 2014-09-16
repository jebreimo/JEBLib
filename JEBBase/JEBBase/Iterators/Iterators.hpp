/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_ITERATORS_ITERATORS_HPP
#define JEBBASE_ITERATORS_ITERATORS_HPP

#include <cassert>
#include <iterator>
#include <stdexcept>
#include <utility>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Iterators {

namespace Throwing {

template <typename FwdIt>
void advance(FwdIt& first, FwdIt last, size_t n, std::forward_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (first == last)
            throw std::range_error("advance beyond end of range");
        ++first;
    }
}

template <typename RndIt>
void advance(RndIt& first, RndIt last, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(first, last);
    assert(len >= 0);
    if ((size_t)len < n)
        throw std::range_error("advance beyond end of range");
    first += n;
}

template <typename It>
It advance(It& first, It last, size_t n = 1)
{
    return advance(first, last, n,
                   typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It next(It first, It last, size_t n = 1)
{
    advance(first, last, n);
    return first;
}

template <typename FwdIt>
void recede(FwdIt first, FwdIt& last, size_t n, std::forward_iterator_tag)
{
    FwdIt it = first;
    for (; n != 0; n--)
    {
        if (first == last)
            throw std::range_error("reced beyond start of range");
        ++first;
    }
    for (; first != last; ++first)
        ++it;
    last = it;
}

template <typename BiIt>
void recede(BiIt first, BiIt& last, size_t n, std::bidirectional_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (first == last)
            throw std::range_error("retreat beyond start of range");
        --last;
    }
}

template <typename RndIt>
void recede(RndIt first, RndIt& last, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(first, last);
    assert(len >= 0);
    if ((size_t)len < n)
        throw std::range_error("retreat beyond start of range");
    last -= n;
}

template <typename It>
void recede(It first, It& last, size_t n = 1)
{
    recede(first, last, n,
           typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It prev(It first, It last, size_t n = 1)
{
    recede(first, last, n);
    return last;
}

template <typename It>
It nth(It first, It last, long steps)
{
    if (steps >= 0)
        return next(first, last, steps);
    else
        return prev(first, last, -steps);
}

}

namespace NonThrowing {

template <typename FwdIt>
void advance(FwdIt& first, FwdIt last, size_t n, std::forward_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (first == last)
            break;
        ++first;
    }
}

template <typename RndIt>
void advance(RndIt& first, RndIt last, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(first, last);
    assert(len >= 0);
    if ((size_t)len < n)
        first = last;
    else
        first += n;
}

template <typename It>
void advance(It& first, It last, size_t n = 1)
{
    advance(first, last, n,
            typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It next(It first, It last, size_t n = 1)
{
    advance(first, last, n);
    return first;
}

template <typename FwdIt>
void recede(FwdIt first, FwdIt& last, size_t n, std::forward_iterator_tag)
{
    FwdIt it = first;
    for (; n != 0; n--)
    {
        if (first == last)
            break;
        ++first;
    }
    for (; first != last; ++first)
        ++it;
    last = it;
}

template <typename BiIt>
void recede(BiIt first, BiIt& last, size_t n, std::bidirectional_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (first == last)
            break;
        --last;
    }
}

template <typename RndIt>
void recede(RndIt first, RndIt& last, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(first, last);
    assert(len >= 0);
    if ((size_t)len < n)
        last = first;
    else
        last -= n;
}

template <typename It>
void recede(It first, It& last, size_t n = 1)
{
    recede(first, last, n,
           typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It prev(It first, It last, size_t n = 1)
{
    recede(first, last, n);
    return last;
}

template <typename It>
It nth(It first, It last, ptrdiff_t steps)
{
    if (steps >= 0)
        return next(first, last, steps);
    else
        return prev(first, last, -steps);
}

}

using namespace NonThrowing;

}}

#endif
