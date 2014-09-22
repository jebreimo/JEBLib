#ifndef JEBSTRING_ENCODEDSTRINGS_DECODEUTF16_HPP
#define JEBSTRING_ENCODEDSTRINGS_DECODEUTF16_HPP

#include <cstdint>
#include <limits>
#include <string>
#include "JEBBase/Bits/Endian.hpp"
#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace EncodedStrings {

using JEBBase::Bits::IsBigEndian;
using JEBBase::Bits::IsLittleEndian;

template <typename FwdIt, bool SwapBytes>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename FwdIt>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename BiIt, bool SwapBytes>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename BiIt>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename FwdIt>
unsigned nextUtf16LECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsBigEndian>(codePoint, it, end);
}

template <typename FwdIt>
unsigned nextUtf16BECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsLittleEndian>(codePoint, it, end);
}

template <typename BiIt>
unsigned prevUtf16LECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsBigEndian>(codePoint, begin, it);
}

template <typename BiIt>
unsigned prevUtf16BECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsLittleEndian>(codePoint, begin, it);
}

}}

#include "DecodeUtf16_impl.hpp"

#endif
