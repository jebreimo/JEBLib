#ifndef JEB_WILDCARDWORD_HPP
#define JEB_WILDCARDWORD_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "CharRangeSet.hpp"

namespace JEB { namespace String { namespace Generic {

class WildcardWord
{
public:
    void add(uint32_t character);
    template <typename StrFwdIt>
    void add(StrFwdIt begin, StrFwdIt end);
    void add(const CharRangeSet& charRange);
    void reverse();

    enum MatchResult {Match, Mismatch, NoMatch};

    template <typename StrFwdIt, typename UnaryFunc>
    std::pair<StrFwdIt, MatchResult>
        startsWith(StrFwdIt begin, StrFwdIt end, UnaryFunc transform) const;

    template <typename StrBiIt, typename UnaryFunc>
    std::pair<StrBiIt, MatchResult>
        endsWith(StrBiIt begin, StrBiIt end, UnaryFunc transform) const;

    template <typename StrFwdIt, typename UnaryFunc>
    std::pair<StrFwdIt, StrFwdIt>
        findFirst(StrFwdIt begin, StrFwdIt end, UnaryFunc transform) const;

    template <typename StrBiIt, typename UnaryFunc>
    std::pair<StrBiIt, StrBiIt>
        findLast(StrBiIt begin, StrBiIt end, UnaryFunc transform) const;
private:
    static const uint32_t c_Range;
    std::vector<uint32_t> m_Chars;
    std::vector<CharRangeSet> m_CharRanges;
};

}}}

#include "WildcardWord_Impl.hpp"

#endif
