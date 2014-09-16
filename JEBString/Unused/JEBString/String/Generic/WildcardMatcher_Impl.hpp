#include <cassert>
#include "EscapedString.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename T>
T identity(T value)
{
    return value;
}

template <typename StrBiIt>
std::pair<StrBiIt, StrBiIt> WildcardMatcher::find(StrBiIt beg, StrBiIt end)
{
    std::vector<WildcardWord>::const_iterator wit = m_Words.begin();
    std::vector<WildcardWord>::const_iterator wend = m_Words.end();
    StrBiIt matchBeg = beg;
    StrBiIt matchEnd = end;
    StrBiIt origEnd = end;

    if (wit != wend && m_HasPrefix)
    {
        std::pair<StrBiIt, StrBiIt> res = (wit++)->findFirst(beg, end, identity<uint32_t>);
        if (res.first == res.second)
            return std::make_pair(origEnd, origEnd);
        beg = res.second;
        matchBeg = res.first;
    }

    if (wit != wend && m_HasSuffix)
    {
        std::pair<StrBiIt, StrBiIt> res = (--wend)->findLast(beg, end, identity<uint32_t>);
        if (res.first == res.second)
            return std::make_pair(origEnd, origEnd);
        end = res.first;
        matchEnd = res.second;
    }

    for (; wit != wend; wit++)
    {
        std::pair<StrBiIt, StrBiIt> res = wit->findFirst(beg, end, identity<uint32_t>);
        if (res.first == res.second)
            return std::make_pair(origEnd, origEnd);
        beg = res.second;
    }

    return std::make_pair(matchBeg, matchEnd);
}

template <typename StrBiIt>
std::pair<StrBiIt, StrBiIt> WildcardMatcher::findShortest(StrBiIt beg, StrBiIt end)
{
    std::vector<WildcardWord>::const_iterator wit = m_Words.begin();
    std::vector<WildcardWord>::const_iterator wend = m_Words.end();
    StrBiIt matchBeg = beg;
    StrBiIt matchEnd = end;

    if (wit != wend)
    {
        std::pair<StrBiIt, StrBiIt> res = (wit++)->findFirst(beg, end, identity<uint32_t>);
        if (res.first == res.second)
            return std::make_pair(end, end);
        matchBeg = res.first;
        matchEnd = beg = res.second;
    }

    for (; wit != wend; wit++)
    {
        std::pair<StrBiIt, StrBiIt> res = wit->findFirst(beg, end, identity<uint32_t>);
        if (res.first == res.second)
            return std::make_pair(end, end);
        matchEnd = beg = res.second;
    }

    return std::make_pair(matchBeg, matchEnd);
}

template <typename StrBiIt>
bool WildcardMatcher::match(StrBiIt beg, StrBiIt end)
{
    std::vector<WildcardWord>::const_iterator wbeg = m_Words.begin();
    std::vector<WildcardWord>::const_iterator wend = m_Words.end();
    if (m_HasPrefix && wbeg != wend)
    {
        std::pair<StrBiIt, WildcardWord::MatchResult> res = (wbeg++)->startsWith(beg, end, identity<uint32_t>);
        if (res.second != WildcardWord::Match)
            return false;
        beg = res.first;
    }
    if (m_HasSuffix && wbeg != wend)
    {
        std::pair<StrBiIt, WildcardWord::MatchResult> res = (--wend)->endsWith(beg, end, identity<uint32_t>);
        if (res.second != WildcardWord::Match)
            return false;
        end = res.first;
    }
    for (; wbeg != wend; wbeg++)
    {
        std::pair<StrBiIt, StrBiIt> its = wbeg->findFirst(beg, end, identity<uint32_t>);
        if (its.first == its.second)
            return false;
        beg = its.second;
    }
    return !m_HasPrefix || !m_HasSuffix || m_Words.size() > 1 || beg == end;
}

template <typename StrFwdIt>
void WildcardMatcher::parse(StrFwdIt begin, StrFwdIt end)
{
    m_Words.clear();
    m_HasPrefix = true;
    m_HasSuffix = false;
    WildcardWord* currentWord = NULL;
    StrFwdIt it = begin;
    while (it != end)
    {
        std::pair<uint32_t, bool> ch = unescapeNext(it, end);
        if (!ch.second && ch.first == '*')
        {
            if (m_Words.empty())
                m_HasPrefix = false;
            currentWord = NULL;
        }
        else
        {
            if (!currentWord)
                currentWord = &newWord();

            if (ch.second)
            {
                currentWord->add(ch.first);
            }
            else if (ch.first == '?')
            {
                CharRangeSet ranges;
                ranges.addAll();
                currentWord->add(ranges);
            }
            else if (ch.first == '[')
            {
                StrFwdIt endOfSet = findFirstUnescaped(it, end, ']');
                if (endOfSet == end)
                    throw std::invalid_argument("\"[\" without corresponding \"]\"");
                currentWord->add(CharRangeSet::parse(it, endOfSet));
                it = ++endOfSet;
            }
            else
            {
                currentWord->add(ch.first);
            }
        }
    }
    m_HasSuffix = currentWord != NULL;
}

template <typename FwidIt>
bool hasWildcards(FwidIt beg, FwidIt end)
{
    bool openBracket = false;
    size_t closedBrackets = 0;
    while (beg != end)
    {
        std::pair<uint32_t, bool> chr = unescapeNext(beg, end);
        if (chr.first == '*' || chr.first == '?')
        {
            return true;
        }
        else if (chr.first == '[' && !chr.second)
        {
            openBracket = true;
        }
        else if (chr.first == ']' && !chr.second)
        {
            if (!openBracket)
                return false;
            openBracket = false;
            closedBrackets++;
        }
    }
    return !openBracket && closedBrackets != 0;
}

}}}
