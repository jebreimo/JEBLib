#ifndef JEBSTRING_ENCODEDSTRINGS_ENCODEUTF16_HPP
#define JEBSTRING_ENCODEDSTRINGS_ENCODEUTF16_HPP

#include <cstdint>
#include <limits>
#include <string>
#include "JEBString/JEBStringDefinitions.hpp"

namespace JEBString { namespace EncodedStrings {

template <typename OutIt, bool SwapBytes>
OutIt addUtf16(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt addUtf16(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt addUtf16LE(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt addUtf16BE(OutIt out, uint32_t codePoint);

template <typename FwdIt>
size_t encodeUtf16(FwdIt& begin, FwdIt end, uint32_t codePoint);
template <typename FwdIt>
size_t encodeUtf16LE(FwdIt& begin, FwdIt end, uint32_t codePoint);
template <typename FwdIt>
size_t encodeUtf16BE(FwdIt& begin, FwdIt end, uint32_t codePoint);

}}

#include "EncodeUtf16_impl.hpp"

#endif
