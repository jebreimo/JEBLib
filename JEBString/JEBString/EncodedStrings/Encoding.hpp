#ifndef JEBSTRING_ENCODEDSTRINGS_ENCODING_HPP
#define JEBSTRING_ENCODEDSTRINGS_ENCODING_HPP

#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace EncodedStrings {

template <Encoding_t Enc>
class Encoding
{
public:
    static const Encoding_t encoding = Enc;

    // These are the functions each implementation of this class are expected
    // to implement:

    // template <typename FwdIt>
    // unsigned nextCodePoint(uint32_t& codePoint, FwdIt& first, FwdIt last);

    // template <typename BiIt>
    // unsigned prevCodePoint(uint32_t& codePoint, BiIt first, FwdIt& BiIt);

    // template <typename OutIt>
    // OutIt encodeCodePoint(OutIt dst, uint32_t codePoint);
};

}}

#endif
