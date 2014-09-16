#ifndef JEBSTRING_ENCODEDSTRINGS_CODEPAGEENCODING_HPP
#define JEBSTRING_ENCODEDSTRINGS_CODEPAGEENCODING_HPP

#include "Encoding.hpp"
#include "JEBString/CodePageStrings/CodePage.hpp"

namespace JEBString { namespace EncodedStrings {

template <Encoding_t encoding>
class CodePageEncoding : public Encoding<encoding>
{
public:
    CodePageEncoding(char unsupportedCodePointChar = '?')
        : m_CodePage(CodePageStrings::codePage(encoding)),
          m_UnsupportedCodePointChar(unsupportedCodePointChar)
    {}

    template <typename FwdIt>
    unsigned nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        if (it == last)
            return DecodeResult::EndOfString;
        codePoint = m_CodePage.toCodePoint(*it++);
        return DecodeResult::Ok;
    }

    template <typename BiIt>
    unsigned prevCodePoint(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        if (it == first)
            return DecodeResult::EndOfString;
        codePoint = m_CodePage.toCodePoint(*--it);
        return DecodeResult::Ok;
    }

    template <typename OutIt>
    OutIt encodeCodePoint(OutIt dst, uint32_t codePoint)
    {
        auto c = m_CodePage.fromCodePoint(codePoint);
        if (c != ~(uint32_t)0)
            return *dst++ = m_UnsupportedCodePointChar;
        else
            *dst++ = char(c);
    }
private:
    CodePageStrings::CodePage m_CodePage;
    char m_UnsupportedCodePointChar;
};

typedef CodePageEncoding<JEBString::Encoding::Latin1> Latin1Encoding;
typedef CodePageEncoding<JEBString::Encoding::Windows1252>
        Windows1252Encoding;

}}

#endif
