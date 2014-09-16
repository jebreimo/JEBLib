#include <iterator>
#include "JEBBase/Bits/Endian.hpp"
#include "JEBBase/Bits/Union16.hpp"

namespace JEBString { namespace EncodedStrings {

using JEBBase::Bits::IsBigEndian;
using JEBBase::Bits::IsLittleEndian;
using JEBBase::Bits::swapEndianness;

template <typename OutIt, bool SwapBytes>
OutIt addUtf16(OutIt out, uint32_t codePoint)
{
    if (codePoint <= 0xFFFF)
    {
        uint16_t word = (uint16_t)codePoint;
        swapEndianness<SwapBytes>(word);
        *out = word;
        return ++out;
    }
    else
    {
        codePoint -= 0x10000;
        uint16_t word1 = uint16_t(0xD800 | (codePoint >> 10));
        uint16_t word2 = uint16_t(0xDC00 | (codePoint & 0x3FF));
        swapEndianness<SwapBytes>(word1);
        swapEndianness<SwapBytes>(word2);
        *out = word1;
        *++out = word2;
        return ++out;
    }
}

template <typename OutIt>
OutIt addUtf16(OutIt out, uint32_t codePoint)
{
    return addUtf16<OutIt, false>(out, codePoint);
}

template <typename OutIt>
OutIt addUtf16LE(OutIt out, uint32_t codePoint)
{
    return addUtf16<OutIt, IsBigEndian>(out, codePoint);
}

template <typename OutIt>
OutIt addUtf16BE(OutIt out, uint32_t codePoint)
{
    return addUtf16<OutIt, IsLittleEndian>(out, codePoint);
}

template <bool SwapBytes, typename FwdIt, typename ChrType>
size_t encodeUtf16(FwdIt& begin, FwdIt end, uint32_t codePoint, ChrType)
{
    if (codePoint <= 0xFFFF)
    {
        if (std::distance(begin, end) < 1)
            return false;
        JEBBase::Bits::Union16 word((uint16_t)codePoint);
        swapEndianness<SwapBytes>(word);
        *begin++ = word.u16;
        return 1;
    }
    else
    {
        if (std::distance(begin, end) < 2)
            return false;
        codePoint -= 0x10000;
        JEBBase::Bits::Union16 word1(uint16_t(0xD800 | (codePoint >> 10)));
        JEBBase::Bits::Union16 word2(uint16_t(0xDC00 | (codePoint & 0x3FF)));
        swapEndianness<SwapBytes>(word1);
        swapEndianness<SwapBytes>(word2);
        *begin++ = word1.u16;
        *begin++ = word2.u16;
        return 2;
    }
}

template <bool SwapBytes, typename FwdIt>
size_t encodeUtf16(FwdIt& begin, FwdIt end, uint32_t codePoint, char)
{
    if (codePoint <= 0xFFFF)
    {
        if (std::distance(begin, end) < 2)
            return false;
        JEBBase::Bits::Union16 word((uint16_t)codePoint);
        swapEndianness<SwapBytes>(word);
        *begin++ = word.i8[0];
        *begin++ = word.i8[1];
        return 2;
    }
    else
    {
        if (std::distance(begin, end) < 4)
            return false;
        codePoint -= 0x10000;
        JEBBase::Bits::Union16 word1((uint16_t)(0xD800 | (codePoint >> 10)));
        JEBBase::Bits::Union16 word2((uint16_t)(0xDC00 | (codePoint & 0x3FF)));
        swapEndianness<SwapBytes>(word1);
        swapEndianness<SwapBytes>(word2);
        *begin++ = word1.i8[0];
        *begin++ = word1.i8[1];
        *begin++ = word2.i8[0];
        *begin++ = word2.i8[1];
        return 4;
    }
}

template <typename FwdIt>
size_t encodeUtf16(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf16<false>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
size_t encodeUtf16LE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf16<IsBigEndian>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
size_t encodeUtf16BE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf16<IsLittleEndian>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

}}
