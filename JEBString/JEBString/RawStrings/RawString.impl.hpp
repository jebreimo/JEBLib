#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBString { namespace RawStrings {

using JEBBase::Ranges::makeRange;

namespace details
{
    template <typename It, typename UnaryFunc1, typename UnaryFunc2>
    Range<It> forEachToken_impl(
            Range<It> str, UnaryFunc1 nextTokenFunc,
            UnaryFunc2 tokenFunc, size_t maxParts,
            SplitFlags_t flags);

    template <typename String, typename ContainerIt, typename DelimiterString>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           const DelimiterString& delimiter,
                           std::input_iterator_tag);

    template <typename String, typename ContainerIt, typename DelimiterString>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           const DelimiterString& delimiter,
                           std::forward_iterator_tag);

    template <typename String, typename ContainerIt>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           std::input_iterator_tag);

    template <typename String, typename ContainerIt>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           std::forward_iterator_tag);
}

template <typename String, typename ContainerIt, typename DelimiterString>
String& appendJoin(String& str, ContainerIt first, ContainerIt last,
                   const DelimiterString& delimiter)
{
    if (first == last)
        return str;

    details::reserveBeforeJoin(str, first, last, delimiter,
            typename std::iterator_traits<ContainerIt>::iterator_category());

    str.insert(end(str), begin(*first), end(*first));
    while (++first != last)
    {
        str.insert(end(str), begin(delimiter), end(delimiter));
        str.insert(end(str), begin(*first), end(*first));
    }
    return str;
}

template <typename String, typename ContainerIt>
String& appendJoin(String& str, ContainerIt first, ContainerIt last)
{
    details::reserveBeforeJoin(str, first, last,
            typename std::iterator_traits<ContainerIt>::iterator_category());
    for (; first != last; ++first)
        str.insert(end(str), begin(*first), end(*first));
    return str;
}

template <typename It, typename UnaryPred, typename UnaryFunc>
Range<It> forEachToken(Range<It> str, UnaryPred delimiter,
                       UnaryFunc tokenFunc, size_t maxParts /*= 0*/,
                       SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return details::forEachToken_impl(
        str, [&](Range<It>& s){return nextToken(s, delimiter);}, tokenFunc,
        maxParts, flags);
}

template <typename String, typename ContainerIt, typename DelimiterString>
String join(ContainerIt first, ContainerIt last,
            const DelimiterString& delimiter)
{
   String result;
   return appendJoin(result, first, last, delimiter);
}

template <typename String, typename ContainerIt>
String join(ContainerIt first, ContainerIt last)
{
   String result;
    return appendJoin(result, first, last);
}

template <typename It, typename UnaryPred>
Range<It> nextToken(Range<It>& str, UnaryPred delimiter)
{
    auto it = find_if(str, delimiter);
    auto first = begin(str);
    str.begin() = JEBBase::Iterators::next(it, end(str));
    return makeRange(first, it);
}

template <typename It, typename UnaryPred>
Range<It> prevToken(Range<It>& str, UnaryPred delimiter)
{
    auto it = findLastIf(str, delimiter);
    auto last = end(str);
    str.end() = it;
    if (it == begin(str) && it != last && !delimiter(*it))
        return makeRange(begin(str), last);
    return makeRange(JEBBase::Iterators::next(it, last), last);
}

template <typename It, typename UnaryPred>
std::vector<Range<It>> splitIf(Range<It> str, UnaryPred delimiter,
                               size_t maxParts /*= 0*/,
                               SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<Range<It>> result;
    forEachToken(str, delimiter, [&](Range<It> r){result.push_back(r);},
                 maxParts, flags);
    return result;
}

template <typename CharType, typename It>
std::basic_string<CharType> toString(Range<It> range)
{
    return std::basic_string<CharType>(begin(range), end(range));
}

namespace details
{
    template <typename It, typename UnaryFunc1, typename UnaryFunc2>
    Range<It> forEachToken_impl(
            Range<It> str, UnaryFunc1 nextTokenFunc,
            UnaryFunc2 tokenFunc, size_t maxParts,
            SplitFlags_t flags)
    {
        while (maxParts != 1 && !empty(str))
        {
            auto token = nextTokenFunc(str);
            if (!SplitFlags::ignoreEmpty(flags) || !empty(token))
            {
                tokenFunc(token);
                --maxParts;
            }
            if (end(token) == end(str))
                return str;
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmpty(flags) || !empty(str)))
        {
            tokenFunc(str);
            str.begin() = str.end();
        }
        return str;
    }

    template <typename String, typename ContainerIt, typename DelimiterString>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           const DelimiterString& delimiter,
                           std::input_iterator_tag)
    {}

    template <typename String, typename ContainerIt, typename DelimiterString>
    size_t lengthOfJoin(const String& str,
                        ContainerIt first, ContainerIt last,
                        const DelimiterString& delimiter)
    {
        size_t n = 0, len = str.size();
        for (; first != last; ++first)
        {
            len += first->size();
            ++n;
        }
        return len + (n - 1) * delimiter.size();
    }

    template <typename String, typename ContainerIt, typename DelimiterString>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           const DelimiterString& delimiter,
                           std::forward_iterator_tag)
    {
        str.reserve(lengthOfJoin(str, first, last, delimiter));
    }

    template <typename String, typename ContainerIt>
    size_t lengthOfJoin(String& str, ContainerIt first, ContainerIt last)
    {
        size_t size = str.size();
        for (; first != last; ++first)
            size += first->size();
        return size;
    }

    template <typename String, typename ContainerIt>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           std::input_iterator_tag)
    {}

    template <typename String, typename ContainerIt>
    void reserveBeforeJoin(String& str, ContainerIt first, ContainerIt last,
                           std::forward_iterator_tag)
    {
        str.reserve(lengthOfJoin(str, first, last));
    }
}
}}
