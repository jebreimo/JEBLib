#include "WildcardWord.hpp"
#include <stdexcept>

namespace JEB { namespace String { namespace Generic {

const uint32_t WildcardWord::c_Range = ~(uint32_t)0;

void WildcardWord::add(uint32_t character)
{
    if (character == c_Range)
        throw std::invalid_argument("wildcard expression can't contain character 0xFFFFFFFF.");
    m_Chars.push_back(character);
}

void WildcardWord::add(const CharRangeSet& charRange)
{
    m_Chars.push_back(c_Range);
    m_CharRanges.push_back(charRange);
}

}}}
