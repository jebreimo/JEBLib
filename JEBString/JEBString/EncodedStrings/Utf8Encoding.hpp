#ifndef JEBSTRING_ENCODEDSTRINGS_UTF8ENCODING_HPP
#define JEBSTRING_ENCODEDSTRINGS_UTF8ENCODING_HPP

#include "Encoding.hpp"
#include "DecodeUtf8.hpp"
#include "EncodeUtf8.hpp"

namespace JEBString { namespace EncodedStrings {

class Utf8Encoding : public Encoding<JEBString::Encoding::Utf8>
{
public:
    template <typename FwdIt>
    unsigned nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        return nextUtf8CodePoint(codePoint, it, last);
    }

    template <typename BiIt>
    unsigned prevCodePoint(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        return prevUtf8CodePoint(codePoint, first, it);
    }

    template <typename OutIt>
    OutIt encodeCodePoint(OutIt dst, uint32_t codePoint)
    {
        return addUtf8(dst, codePoint);
    }
};

}}

#endif
