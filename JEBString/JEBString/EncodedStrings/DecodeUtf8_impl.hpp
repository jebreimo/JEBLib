#include <algorithm>
#include <cassert>

namespace JEBString { namespace EncodedStrings {

using JEBString::DecodeResult;

namespace internal
{
    static inline bool isContinuation(uint8_t c)
    {
        return (c & 0xC0) == 0x80;
    }

    static inline bool isAscii(uint32_t c)
    {
        return  (c & 0x80) == 0;
    }
}

template <typename FwdIt>
bool isValidUtf8(FwdIt begin, FwdIt end, bool acceptIncomleteAtEnd)
{
    unsigned cp;
    unsigned result;
    while ((result = nextUtf8CodePoint(cp, begin, end)) == 0)
    {
    }
    return result == DecodeResult::EndOfString ||
           (acceptIncomleteAtEnd && (result & DecodeResult::EndOfString));
}

template <typename FwdIt>
bool skipNextUtf8CodePoint(FwdIt& it, FwdIt end)
{
    if (it == end)
        return false;

    do
    {
        ++it;
    }
    while (it != end && internal::isContinuation(*it));

    return true;
}

template <typename FwdIt>
unsigned nextUtf8CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    if (it == end)
        return DecodeResult::EndOfString;

    if (internal::isAscii(*it))
    {
        codePoint = (uint8_t)*it++;
        return DecodeResult::Ok;
    }

    if (internal::isContinuation(*it) || uint8_t(*it) >= 0xFE)
        return DecodeResult::Invalid;

    size_t count = 1;
    unsigned bit = 0x20;
    codePoint = *it & 0x3F;
    while (codePoint & bit)
    {
        bit >>= 1;
        ++count;
    }

    codePoint &= bit - 1;

    if (!codePoint)
        return DecodeResult::Invalid;

    FwdIt initialIt = it;
    while (++it != end && count && internal::isContinuation(*it))
    {
        codePoint <<= 6;
        codePoint |= *it & 0x3F;
        --count;
    }

    if (count)
    {
        unsigned result = DecodeResult::Incomplete;
        if (it == end)
            result |= DecodeResult::EndOfString;
        it = initialIt;
        return result;
    }

    return DecodeResult::Ok;
}

template <typename BiIt>
unsigned prevUtf8CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    if (it == begin)
        return DecodeResult::EndOfString;

    BiIt initialIt = it;
    --it;
    if (internal::isAscii(*it))
    {
        codePoint = (uint8_t)*it;
        return DecodeResult::Ok;
    }

    codePoint = 0;
    uint8_t mask = 0xC0;
    uint8_t bit = 0x20;
    uint32_t shift = 0;
    while (internal::isContinuation(*it))
    {
        if (bit == 1 || it == begin)
        {
            it = initialIt;
            return DecodeResult::Invalid;
        }
        mask |= bit;
        bit >>= 1;
        codePoint |= uint32_t(*it & 0x3F) << shift;
        shift += 6;
        --it;
    }

    uint8_t byte = *it;
    if ((byte & mask) != uint8_t(mask << 1))
    {
        it = initialIt;
        if ((byte & mask) != mask)
            return DecodeResult::Invalid;
        else
            return DecodeResult::Incomplete;
    }

    if ((byte & ~mask) == 0)
    {
        it = initialIt;
        return DecodeResult::Invalid;
    }

    codePoint |= (byte & ~mask) << shift;

    return DecodeResult::Ok;
}

}}
