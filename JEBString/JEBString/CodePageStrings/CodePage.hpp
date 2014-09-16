#ifndef JEBSTRING_CODEPAGES_CODEPAGE_HPP
#define JEBSTRING_CODEPAGES_CODEPAGE_HPP

#include <cstddef>
#include <cstdint>
#include <utility>
#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace CodePageStrings {

typedef std::pair<uint32_t, uint8_t> CodePointMapping;

class CodePage
{
public:
    CodePage(const uint32_t* toCodePoints,
             const CodePointMapping* firstFromCodePoints,
             const CodePointMapping* lastFromCodePoints,
             JEBString::Encoding_t encoding);

    uint32_t toCodePoint(char c) const;
    uint32_t fromCodePoint(uint32_t c) const;
    JEBString::Encoding_t encoding() const;
private:
    const uint32_t* m_ToCodePoints;
    const std::pair<uint32_t, uint8_t>* m_FirstFromCodePoints;
    const std::pair<uint32_t, uint8_t>* m_LastFromCodePoints;
    JEBString::Encoding_t m_Encoding;
};

CodePage codePage(Encoding_t encoding);

}}

#endif
