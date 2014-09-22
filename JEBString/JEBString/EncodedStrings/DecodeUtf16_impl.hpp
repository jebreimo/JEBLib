#include "JEBBase/Bits/Union16.hpp"
#include "JEBBase/Bits/Integers.hpp"

namespace JEBString { namespace EncodedStrings {

typedef JEBBase::Bits::EquvalentUnsignedIntType<sizeof(wchar_t)>::Type
        JEB_wchar_alias;

namespace internal
{
    using JEBBase::Bits::swapEndianness;

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint32_t)
    {
        if (it == end)
            return DecodeResult::EndOfString;
        else if (*it > 0xFFFFu)
            return DecodeResult::Invalid;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecodeResult::Ok;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, uint32_t)
    {
        if (it == begin)
            return DecodeResult::EndOfString;
        else if (*it > 0xFFFFu)
            return DecodeResult::Invalid;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecodeResult::Ok;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint16_t)
    {
        if (it == end)
            return DecodeResult::EndOfString;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecodeResult::Ok;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, uint16_t)
    {
        if (it == begin)
            return DecodeResult::EndOfString;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecodeResult::Ok;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, char)
    {
        if (it == end)
            return DecodeResult::EndOfString;

        FwdIt initialIt = it;
        JEBBase::Bits::Union16 chr;
        chr.u8[SwapBytes ? 1 : 0] = *it++;

        if (it == end)
        {
            it = initialIt;
            return DecodeResult::Incomplete | DecodeResult::EndOfString;
        }

        chr.u8[SwapBytes ? 0 : 1] = *it++;

        word = chr.u16;
        return DecodeResult::Ok;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, char)
    {
        if (it == begin)
            return DecodeResult::EndOfString;

        BiIt initialIt = it;
        JEBBase::Bits::Union16 chr;
        chr.u8[SwapBytes ? 0 : 1] = *(--it);

        if (it == begin)
        {
            it = initialIt;
            return DecodeResult::Incomplete | DecodeResult::EndOfString;
        }

        chr.u8[SwapBytes ? 1 : 0] = *(--it);

        word = chr.u16;
        return DecodeResult::Ok;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, wchar_t)
    {
        return nextWord<FwdIt, SwapBytes>(word, it, end, JEB_wchar_alias());
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, wchar_t)
    {
        return prevWord<BiIt, SwapBytes>(word, begin, it, JEB_wchar_alias());
    }
}

template <typename FwdIt, bool SwapBytes>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    uint16_t chr;
    unsigned nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult != DecodeResult::Ok)
        return nwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Ok;
    }
    else if (0xDC00 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Invalid;
    }

    codePoint = (chr & 0x3FF) << 10;

    nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult == DecodeResult::EndOfString)
        return DecodeResult::EndOfString | DecodeResult::Incomplete;
    else if (nwResult != DecodeResult::Ok)
        return nwResult;

    if (chr < 0xDC00 || 0xE000 <= chr)
    {
        codePoint |= chr;
        return DecodeResult::Invalid;
    }

    codePoint |= chr & 0x3FF;
    codePoint += 0x10000;

    return DecodeResult::Ok;
}

template <typename FwdIt>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, false>(codePoint, it, end);
}

template <typename BiIt, bool SwapBytes>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    uint16_t chr;
    unsigned pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, begin, it,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult != DecodeResult::Ok)
        return pwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Ok;
    }
    else if (chr < 0xDC00)
    {
        codePoint = chr;
        return DecodeResult::Invalid;
    }

    codePoint = chr & 0x3FF;

    pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, begin, it,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult == DecodeResult::EndOfString)
        return DecodeResult::EndOfString | DecodeResult::Incomplete;
    else if (pwResult != DecodeResult::Ok)
        return pwResult;

    if (chr < 0xD800 || 0xDC00 <= chr)
    {
        codePoint |= chr << 10;
        return DecodeResult::Invalid;
    }

    codePoint |= (chr & 0x3FF) << 10;
    codePoint += 0x10000;

    return DecodeResult::Ok;
}

template <typename BiIt>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, false>(codePoint, begin, it);
}

}}
