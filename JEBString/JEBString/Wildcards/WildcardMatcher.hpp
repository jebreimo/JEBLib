#ifndef JEB_WILDCARDMATCHER_HPP
#define JEB_WILDCARDMATCHER_HPP

#include <vector>
#include "WildcardWord.hpp"

namespace JEB { namespace String { namespace Generic {

class WildcardMatcher
{
public:
    WildcardMatcher();
    ~WildcardMatcher();

    template <typename StrFwdIt>
    void parse(StrFwdIt begin, StrFwdIt end);

    bool hasPrefix() const;
    void setHasPrefix(bool hasPrefix);

    bool hasSuffix() const;
    void setHasSuffix(bool hasSuffix);

    size_t numberOfWords() const;

    template <typename StrBiIt>
    std::pair<StrBiIt, StrBiIt> find(StrBiIt beg, StrBiIt end);

    template <typename StrBiIt>
    std::pair<StrBiIt, StrBiIt> findShortest(StrBiIt beg, StrBiIt end);

    template <typename StrBiIt>
    bool match(StrBiIt beg, StrBiIt end);
private:
    WildcardWord& newWord();

    bool m_HasPrefix;
    bool m_HasSuffix;
    std::vector<WildcardWord> m_Words;
};

template <typename FwidIt>
bool hasWildcards(FwidIt beg, FwidIt end);

}}}

#include "WildcardMatcher_Impl.hpp"

#endif
