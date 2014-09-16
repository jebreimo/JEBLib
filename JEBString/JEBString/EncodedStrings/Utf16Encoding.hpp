#ifndef JEBSTRING_ENCODEDSTRINGS_UTF16ENCODING_HPP
#define JEBSTRING_ENCODEDSTRINGS_UTF16ENCODING_HPP

#include "Encoding.hpp"
#include "DecodeUtf16.hpp"
#include "EncodeUtf16.hpp"

namespace JEBString { namespace EncodedStrings {

class Utf16Encoding : public Encoding<JEBString::Encoding::Utf16>
{
public:
    template <typename FwdIt>
    unsigned nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        return nextUtf16CodePoint(codePoint, it, last);
    }

    template <typename BiIt>
    unsigned prevCodePoint(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        return prevUtf16CodePoint(codePoint, first, it);
    }

    template <typename OutIt>
    OutIt encodeCodePoint(OutIt dst, uint32_t codePoint)
    {
        return addUtf16(dst, codePoint);
    }
};

}}

#endif
