#include "WildcardMatcher.hpp"

namespace JEB { namespace String { namespace Generic {

WildcardMatcher::WildcardMatcher()
    : m_HasPrefix(false),
      m_HasSuffix(false)
{}

WildcardMatcher::~WildcardMatcher()
{}

bool WildcardMatcher::hasPrefix() const
{
    return m_HasPrefix;
}

void WildcardMatcher::setHasPrefix(bool hasPrefix)
{
    m_HasPrefix = hasPrefix;
}

bool WildcardMatcher::hasSuffix() const
{
    return m_HasSuffix;
}

void WildcardMatcher::setHasSuffix(bool hasSuffix)
{
    m_HasSuffix = hasSuffix;
}

WildcardWord& WildcardMatcher::newWord()
{
    m_Words.push_back(WildcardWord());
    return m_Words.back();
}

size_t WildcardMatcher::numberOfWords() const
{
    return m_Words.size();
}

}}}
