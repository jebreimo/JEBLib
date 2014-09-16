#include <cassert>
#include "EscapedString.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename StrFwdIt>
void WildcardWord::add(StrFwdIt begin, StrFwdIt end)
{
    for (StrFwdIt it = begin; it != end; it++)
        add(static_cast<uint32_t>(*it));
}

template <typename StrFwdIt, typename UnaryFunc>
std::pair<StrFwdIt, WildcardWord::MatchResult>
    WildcardWord::startsWith(StrFwdIt begin, StrFwdIt end, UnaryFunc transform) const
{
    std::vector<CharRangeSet>::const_iterator range = m_CharRanges.begin();
    for (std::vector<uint32_t>::const_iterator it = m_Chars.begin(); it != m_Chars.end(); it++)
    {
        if (begin == end)
            return std::make_pair(begin, NoMatch);
        else if (*begin == c_Range)
            throw std::invalid_argument("Can't match strings containing character 0xFFFFFFFF.");
        else if (transform(*it) != *begin &&
                 (*it != c_Range || !(*range++).has(transform(*begin))))
            return std::make_pair(begin, Mismatch);
        begin++;
    }
    return std::make_pair(begin, Match);
}

template <typename StrBiIt, typename UnaryFunc>
std::pair<StrBiIt, WildcardWord::MatchResult>
    WildcardWord::endsWith(StrBiIt begin, StrBiIt end, UnaryFunc transform) const
{
    std::vector<CharRangeSet>::const_iterator range = m_CharRanges.end();
    for (std::vector<uint32_t>::const_iterator it = m_Chars.end(); it != m_Chars.begin();)
    {
        if (end == begin)
            return std::make_pair(end, NoMatch);
        --end;
        if (*end == c_Range)
            throw std::invalid_argument("Can't match strings containing character 0xFFFFFFFF.");
        --it;
        if (transform(*it) != transform(*end) &&
            (*it != c_Range || !(*--range).has(transform(*end))))
            return std::make_pair(end, Mismatch);
    }
    return std::make_pair(end, Match);
}

template <typename StrFwdIt, typename UnaryFunc>
std::pair<StrFwdIt, StrFwdIt>
    WildcardWord::findFirst(StrFwdIt begin, StrFwdIt end, UnaryFunc transform) const
{
    for (; begin != end; ++begin)
    {
        std::pair<StrFwdIt, MatchResult> res = startsWith(begin, end, transform);
        if (res.second == Match)
            return std::make_pair(begin, res.first);
        else if (res.second == NoMatch)
            return std::make_pair(end, end);
    }
    // The following return is purely for cosmetic reasons.
    // startsWith should always return Match or NoMatch at some point in the
    // for-loop, so we should never get here.
    return std::make_pair(end, end);
}

template <typename StrFwdIt, typename UnaryFunc>
std::pair<StrFwdIt, StrFwdIt>
    WildcardWord::findLast(StrFwdIt begin, StrFwdIt end, UnaryFunc transform) const
{
    for (; end != begin; --end)
    {
        std::pair<StrFwdIt, MatchResult> res = endsWith(begin, end, transform);
        if (res.second == Match)
            return std::make_pair(res.first, end);
        else if (res.second == NoMatch)
            return std::make_pair(end, end);
    }
    // The following return is purely for cosmetic reasons.
    // endsWith should always return Match or NoMatch at some point in the
    // for-loop, so we should never get here.
    return std::make_pair(end, end);
}

}}}
