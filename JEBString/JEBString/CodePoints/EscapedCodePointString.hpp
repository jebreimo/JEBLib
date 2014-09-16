#ifndef JEBSTRING_CODEPOINTS_ESCAPEDSTRING_HPP
#define JEBSTRING_CODEPOINTS_ESCAPEDSTRING_HPP

#include <cstdint>
#include "CodePointIterator.hpp"

namespace JEBString { namespace CodePoints {

// TODO: function that produce escaped string

template <typename Decoder>
uint32_t fromHex(CodePointIterator<Decoder>& it, size_t length)
{
    uint32_t value = 0;
    for (size_t i = 0; i < length; ++i)
    {
        uint32_t ch;
        if (!it.next(ch))
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        value *= 16;
        if ('0' <= ch && ch <= '9')
            ch += ch - '0';
        else if ('A' <= ch && ch <= 'F')
            ch += ch - 'A' + 10;
        else if ('a' <= ch && ch <= 'f')
            ch += ch - 'a' + 10;
        else
            throw std::invalid_argument(
                    "Hexadecimal sequence contains invalid characters.");
    }
    return value;
}

template <typename Decoder>
bool unescapeNext(CodePointIterator<Decoder>& it, uint32_t& chr,
                  bool& escaped, uint32_t escapeChar = '\\')
{
    escaped = false;
    if (!it.next(chr))
        return false;

    if (chr != escapeChar)
        return true;

    if (!it.next(chr))
        throw std::invalid_argument("Invalid escaped character.");

    escaped = true;
    switch (chr)
    {
    case '0': chr = '\0'; break;
    case 'U': chr = fromHex(it, 8); break;
    case 'a': chr = '\a'; break;
    case 'b': chr = '\b'; break;
    case 'f': chr = '\f'; break;
    case 'n': chr = '\n'; break;
    case 'r': chr = '\r'; break;
    case 't': chr = '\t'; break;
    case 'v': chr = '\v'; break;
    case 'u': chr = fromHex(it, 4); break;
    case 'x': chr = fromHex(it, 2); break;
    default: break;
    }

    return true;
}

template <typename Decoder>
std::pair<uint32_t, bool> unescapeNext(CodePointIterator<Decoder>& it,
                                       uint32_t escapeChar = '\\')
{
    std::pair<uint32_t, bool> result;
    unescapeNext(it, result.first, result.second, escapeChar);
    return result;
}

// template <typename FwdIt, typename UnaryPred>
// FwdIt findFirstUnescapedIf(Range<FwdIt> str, UnaryPred predicate)
// {
//     bool escaped = false;
//     for (auto it = begin(str); it != end(str); ++it)
//     {
//         if (escaped)
//             escaped = false;
//         else if (*it == '\\')
//             escaped = true;
//         else if (predicate(*it))
//             return it;
//     }
//     return end(str);
// }

// template <typename FwdIt, typename UnaryPred>
// FwdIt findFirstUnescapedIfNot(Range<FwdIt> str, UnaryPred predicate)
// {
//     return findFirstUnescapedIf(str, [&](uint32_t c){return !predicate(c);});
// }

// template <typename FwdIt>
// FwdIt findFirstUnescaped(Range<FwdIt> str, uint32_t chr)
// {
//     return findFirstUnescapedIf(str, [&](uint32_t c){return c == chr;});
// }

// template <typename FwdIt1, typename FwdIt2>
// FwdIt1 findFirstUnescapedOf(Range<FwdIt1> str, Range<FwdIt2> cmp)
// {
//     return findFirstUnescapedIf(
//             str, [&](uint32_t c){return find(cmp, c) != end(cmp);});
// }

// template <typename FwdIt1, typename FwdIt2>
// FwdIt1 findFirstUnescapedNotOf(Range<FwdIt1> str, Range<FwdIt2> cmp)
// {
//     return findFirstUnescapedIf(
//             str, [&](uint32_t c){return find(cmp, c) == end(cmp);});
// }

}}

#endif
