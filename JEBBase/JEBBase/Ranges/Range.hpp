/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_RANGES_RANGE_HPP
#define JEBBASE_RANGES_RANGE_HPP

#include <cstring>
#include <cwchar>
#include <iterator>
#include <utility>
#include "JEBBase/Iterators/Iterators.hpp"

namespace JEBBase { namespace Ranges {

template <typename Iterator>
class Range
{
public:
    typedef Iterator iterator;
    typedef std::iterator_traits<Iterator> iterator_traits;
    typedef typename iterator_traits::value_type value_type;
    typedef typename iterator_traits::difference_type difference_type;
    typedef typename iterator_traits::pointer pointer;
    typedef typename iterator_traits::reference reference;
    typedef typename iterator_traits::iterator_category iterator_category;

    Range()
    {}

    Range(Iterator first, Iterator last)
        : m_Range(first, last)
    {}

    Range(std::pair<Iterator, Iterator> range)
        : m_Range(range)
    {}

    operator std::pair<Iterator, Iterator>()
    {
        return m_Range;
    }

    Iterator& begin()
    {
        return m_Range.first;
    }

    Iterator begin() const
    {
        return m_Range.first;
    }

    Iterator& end()
    {
        return m_Range.second;
    }

    Iterator end() const
    {
        return m_Range.second;
    }
private:
    std::pair<Iterator, Iterator> m_Range;
};

template <typename Iterator>
void advance(Range<Iterator>& range, size_t n)
{
    Iterators::advance(range.begin(), range.end(), n);
}

template <typename Iterator>
Iterator next(Range<Iterator> range, size_t n)
{
    return Iterators::next(range.begin(), range.end(), n);
}

template <typename Iterator>
void recede(Range<Iterator>& range, size_t n)
{
    Iterators::recede(range.begin(), range.end(), n);
}

template <typename Iterator>
Iterator prev(Range<Iterator> range, size_t n)
{
    return Iterators::prev(range.begin(), range.end(), n);
}

template <typename Iterator>
Iterator begin(Range<Iterator> range)
{
    return range.begin();
}

template <typename Iterator>
Iterator end(Range<Iterator> range)
{
    return range.end();
}

template <typename Iterator>
Iterator nth(Range<Iterator> range, ptrdiff_t index)
{
    return Iterators::nth(begin(range), end(range), index);
}

template <typename Iterator>
bool empty(const Range<Iterator>& range)
{
    return begin(range) == end(range);
}

template <typename Iterator>
auto front(Range<Iterator> range) -> decltype(*range.begin())
{
    return *range.begin();
}

template <typename Iterator>
auto back(Range<Iterator> range) -> decltype(*range.end())
{
    return *--range.end();
}

template <typename Iterator>
Range<Iterator> frontRange(Range<Iterator> range)
{
    return Range<Iterator>(range.begin(), range.begin());
}

template <typename Iterator>
Range<Iterator> endRange(Range<Iterator> range)
{
    return Range<Iterator>(range.end(), range.end());
}

template <typename Iterator>
Range<Iterator> makeRange(Iterator first, Iterator last)
{
    return Range<Iterator>(first, last);
}

template <typename Container>
auto makeRange(const Container& c) -> Range<decltype(begin(c))>
{
    return makeRange(begin(c), end(c));
}

template <typename Container>
auto makeRange(Container& c) -> Range<decltype(begin(c))>
{
    return makeRange(begin(c), end(c));
}

template <typename T, size_t N>
Range<T*> makeRange(T (&a)[N])
{
    return makeRange(a, a + N);
}

template <typename T, size_t N>
Range<const T*> makeRange(const T (&a)[N])
{
    return makeRange(a, a + N);
}

template <size_t N>
Range<const char*> makeRange(const char (&s)[N])
{
    if (s[N - 1])
        return makeRange(s, s + N);
    else
        return makeRange(s, s + (N - 1));
}

template <size_t N>
Range<const wchar_t*> makeRange(const wchar_t (&s)[N])
{
    if (s[N - 1])
        return makeRange(s, s + N);
    else
        return makeRange(s, s + (N - 1));
}

inline Range<const char*> makeRange(const char* s)
{
    return makeRange(s, s + std::strlen(s));
}

inline Range<const wchar_t*> makeRange(const wchar_t* s)
{
    return makeRange(s, s + std::wcslen(s));
}

template <typename Iterator>
Range<Iterator> makeRange(std::pair<Iterator, Iterator> p)
{
    return Range<Iterator>(p);
}

template <typename BiIt>
std::reverse_iterator<BiIt> makeReverseIterator(BiIt it)
{
    return std::reverse_iterator<BiIt>(it);
}

template <typename Iterator>
Range<std::reverse_iterator<Iterator>> makeReverseRange(Range<Iterator> range)
{
    return makeRange(makeReverseIterator(end(range)),
                     makeReverseIterator(begin(range)));
}

template <typename Iterator>
size_t size(const Range<Iterator>& range)
{
    return std::distance(begin(range), end(range));
}

template <typename Iterator>
Range<Iterator> subrange(const Range<Iterator>& range, ptrdiff_t first, ptrdiff_t last)
{
    return makeRange(nth(range, first), nth(range, last));
}

template <typename Iterator>
Range<Iterator> takeHead(Range<Iterator>& range, Iterator splitPos)
{
    auto b = begin(range);
    range.begin() = splitPos;
    return makeRange(b, splitPos);
}

template <typename Iterator>
Range<Iterator> takeTail(Range<Iterator>& range, Iterator splitPos)
{
    auto e = end(range);
    range.end() = splitPos;
    return makeRange(splitPos, e);
}

template <typename It, typename T>
It transformIterator(It it, T)
{
    return it;
}

template <typename Container, typename Iterator>
Container& appendRange(Container& c, Iterator first, Iterator last)
{
    c.insert(end(c),
             transformIterator(first, typename Container::value_type()),
             transformIterator(last, typename Container::value_type()));
    return c;
}

template <typename Container, typename Iterator>
Container& appendRange(Container& c, Range<Iterator> range)
{
    return appendRange(c, begin(range), end(range));
}

template <typename Container, typename Iterator>
Container fromRange(Range<Iterator> range)
{
    return Container(begin(range), end(range));
}

}}

#endif
