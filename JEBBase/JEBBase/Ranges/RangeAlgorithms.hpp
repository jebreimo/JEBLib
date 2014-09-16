/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_RANGES_RANGEALGORITHMS_HPP
#define JEBBASE_RANGES_RANGEALGORITHMS_HPP

#include "JEBBase/Algorithms/Algorithms.hpp"
#include "Range.hpp"

namespace JEBBase { namespace Ranges {

template <typename FwdIt1, typename FwdIt2>
auto compare(Range<FwdIt1> range1, Range<FwdIt2> range2)
    -> decltype(*range1.begin() - *range2.begin())
{
    return Algorithms::compare(begin(range1), end(range1),
                               begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryFunc>
auto compare(Range<FwdIt1> range1, Range<FwdIt2> range2,
             BinaryFunc cmp)
    -> decltype(cmp(*begin(range1), *begin(range2)))
{
    return Algorithms::compare(begin(range1), end(range1),
                               begin(range2), end(range2),
                               cmp);
}

template <typename FwdIt, typename OutIt>
OutIt copy(Range<FwdIt> src, OutIt dst)
{
    return std::copy(begin(src), end(src), dst);
}

template <typename FwdIt, typename T>
size_t count(Range<FwdIt> range, const T& value)
{
    return std::count(begin(range), end(range), value);
}

template <typename FwdIt, typename UnaryPred>
size_t count_if(Range<FwdIt> range, UnaryPred pred)
{
    return std::count_if(begin(range), end(range), pred);
}

template <typename FwdIt1, typename FwdIt2>
bool equal(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Algorithms::equal(begin(range1), end(range1),
                             begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
bool equal(Range<FwdIt1> range1, Range<FwdIt2> range2,
           BinaryPred predicate)
{
    return Algorithms::equal(begin(range1), end(range1),
                             begin(range2), end(range2),
                             predicate);
}

template <typename FwdIt, typename Value>
FwdIt find(Range<FwdIt> range, const Value& value)
{
    return std::find(begin(range), end(range), value);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_if(Range<FwdIt> range, UnaryPred predicate)
{
    return std::find_if(begin(range), end(range), predicate);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_if_not(Range<FwdIt> range, UnaryPred predicate)
{
    return std::find_if_not(begin(range), end(range), predicate);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_end_if(Range<FwdIt> range, UnaryPred predicate)
{
    return Algorithms::find_end_if(begin(range), end(range), predicate);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_end_if_not(Range<FwdIt> range, UnaryPred predicate)
{
    return Algorithms::find_end_if_not(begin(range), end(range), predicate);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_last_if(Range<FwdIt> range, UnaryPred predicate)
{
    return Algorithms::find_last_if(begin(range), end(range), predicate);
}

template <typename FwdIt, typename UnaryPred>
FwdIt find_last_if_not(Range<FwdIt> range, UnaryPred predicate)
{
    return Algorithms::find_last_if_not(begin(range), end(range), predicate);
}

template <typename FwdIt, typename Value>
bool has(Range<FwdIt> range, const Value& value)
{
    return find(range, value) != end(range);
}

template <typename FwdIt1, typename FwdIt2>
bool less(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Algorithms::less(begin(range1), end(range1),
                            begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2,
          typename BinaryPredicate1, typename BinaryPredicate2>
bool less(Range<FwdIt1> range1, Range<FwdIt2> range2,
          BinaryPredicate1 isEqual,
          BinaryPredicate2 isLess)
{
    return Algorithms::less(begin(range1), end(range1),
                            begin(range2), end(range2),
                            isEqual, isLess);
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt2> mismatch(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Algorithms::mismatch(begin(range1), end(range1),
                                begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
std::pair<FwdIt1, FwdIt2> mismatch(Range<FwdIt1> range1, Range<FwdIt2> range2,
                                   BinaryPred predicate)
{
    return Algorithms::mismatch(begin(range1), end(range1),
                                begin(range2), end(range2),
                                predicate);
}

template <typename FwdIt1, typename FwdIt2>
Range<FwdIt1> search(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Algorithms::search(begin(range1), end(range1),
                              begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
Range<FwdIt1> search(Range<FwdIt1> range1, Range<FwdIt2> range2,
                     BinaryPred predicate)
{
    return Algorithms::search(begin(range1), end(range1),
                              begin(range2), end(range2),
                              predicate);
}

template <typename FwdIt1, typename FwdIt2>
Range<FwdIt1> search_last(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Algorithms::search_last(begin(range1), end(range1),
                                   begin(range2), end(range2));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
Range<FwdIt1> search_last(Range<FwdIt1> range1, Range<FwdIt2> range2,
                          BinaryPred predicate)
{
    return Algorithms::search_last(begin(range1), end(range1),
                                   begin(range2), end(range2),
                                   predicate);
}

template <typename InIt, typename OutIt, typename UnaryFunc>
OutIt transform(Range<InIt> range, OutIt dst, UnaryFunc func)
{
    return std::transform(begin(range), end(range), dst, func);
}

}}

#endif
