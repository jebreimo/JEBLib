#ifndef JEBSTRING_UNICODE_UNICODEPREDICATES_HPP
#define JEBSTRING_UNICODE_UNICODEPREDICATES_HPP

#include <cstdint>
#include "CharClass.hpp"
#include "UnicodeChars.hpp"

namespace JEBString { namespace Unicode {

inline bool isAlphaNumeric(uint32_t c)
{
    return (charClass(c) & (CharClass::Letter | CharClass::Number)) != 0;
}

inline bool isCasedLetter(uint32_t c)
{
    return (charClass(c) & CharClass::CasedLetter) != 0;
}

inline bool isControl(uint32_t c)
{
    return (charClass(c) & CharClass::Control) != 0;
}

inline bool isFormat(uint32_t c)
{
    return (charClass(c) & CharClass::Format) != 0;
}

inline bool isGraphical(uint32_t c)
{
    return (charClass(c) & (CharClass::Letter |
                            CharClass::Mark |
                            CharClass::Number |
                            CharClass::Punctuation |
                            CharClass::Symbol)) != 0;
}

inline bool isHexDigit(uint32_t c)
{
    return ('0' <= c && c <= '9') ||
           ('A' <= c && c <= 'F') ||
           ('a' <= c && c <= 'f');
}

inline bool isLetter(uint32_t c)
{
    return (charClass(c) & CharClass::Letter) != 0;
}

inline bool isMark(uint32_t c)
{
    return (0x300 <= c && c < 0x370) ||
           ((c & 0xFFFFFFC0) == 0x1DC0) ||
           (0x20D0 <= c && c < 0x2100) ||
           ((c & 0xFFFFFFF0) == 0xFE20);
}

inline bool isNewline(uint32_t c)
{
    return c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
           c == Unicode::NextLine || c == Unicode::LineSeparator ||
           c == Unicode::ParagraphSeparator;
}

inline bool isNumber(uint32_t c)
{
    return (charClass(c) & CharClass::Number) != 0;
}

inline bool isPunctuation(uint32_t c)
{
    return (charClass(c) & CharClass::Punctuation) != 0;
}

inline bool isSeparator(uint32_t c)
{
    return (charClass(c) & CharClass::Separator) != 0;
}

inline bool isSurrogate(uint32_t c)
{
    return (charClass(c) & CharClass::Surrogate) != 0;
}

inline bool isSymbol(uint32_t c)
{
    return (charClass(c) & CharClass::Symbol) != 0;
}

inline bool isVisible(uint32_t c)
{
    return (charClass(c) & (CharClass::Letter |
                            CharClass::Mark |
                            CharClass::Number |
                            CharClass::Punctuation |
                            CharClass::Symbol |
                            CharClass::Separator)) != 0;
}

inline bool isWhitespace(uint32_t c)
{
    return c == '\t' || c == ' ' || isNewline(c) ||
           (c > 128 && (charClass(c) & CharClass::Separator) != 0);
}

}}

#endif
