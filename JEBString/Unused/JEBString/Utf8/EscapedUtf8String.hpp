#ifndef JEB_STRING_UTF8_ESCAPEDSTRING_HPP
#define JEB_STRING_UTF8_ESCAPEDSTRING_HPP

#include <stdexcept>
// #include "JEB/Unicode/UnicodeChars.hpp"
#include "JEB/UnicodeString/GenericEscapedString.hpp"
#include "Utf8Iterators.hpp"

namespace JEB { namespace Utf8 {

// template <typename StrInpIt>
// uint32_t fromHex(StrInpIt& beg, StrInpIt end, size_t length)
// {
//     uint32_t ch = 0;
//     for (size_t i = 0; i < length; i++)
//     {
//         uint32_t tmp;
//         if (nextCodePoint(tmp, beg, end) != DecodeResult::Ok)
//             throw std::invalid_argument("Hexadecimal sequence is too short.");
//         ch *= 16;
//         if (uint32_t(tmp - '0') < 10)
//             ch += tmp - '0';
//         else if (uint32_t((tmp | 0x20) - 'a') < 6)
//             ch += 10 + (tmp | 0x20) - 'a';
//         else
//             throw std::invalid_argument("Hexadecimal sequence is too short.");
//     }
//     return ch;
// }

/** Advances @a beg past the next character, returning its (unescaped) value.
 *
 *  Escaped characters:
 *   \\0 \\a \\b \\f \\n \\r \\t \\v \\u#### \\U######## \x##
 *
 *  @not If the string ends with a single escape character, the return value
 *      is the tuple (@a escapeChar, @a false). This is the only circumstance
 *      where that value can be returned.
 *
 *  @returns A pair consisting of the next character and a flag indicating
 *      whether or not the character was escaped. If the character was
 *      escaped, it is the unescaped value that is returned.
 */
template <typename FwdIt>
std::pair<uint32_t, bool> unescapeNextUtf8(FwdIt& first, FwdIt last,
                                           uint32_t escapeChar = '\\')
{
    auto it = beginUtf8Fwd(first, last);
    auto result = String::unescapeNext(it, endUtf8Fwd(last, last),
                                       escapeChar);
    first = beginInternal(it);
    return result;
    // uint32_t ch = Unicode::Invalid;
    // if (nextCodePoint(ch, beg, end) != DecodeResult::Ok ||
    //                   ch != escapeChar ||
    //                   nextCodePoint(ch, beg, end) != DecodeResult::Ok)
    //     return std::make_pair(ch, false);

    // switch (ch)
    // {
    // case '0': ch = '\0'; break;
    // case 'a': ch = '\a'; break;
    // case 'b': ch = '\b'; break;
    // case 'f': ch = '\f'; break;
    // case 'n': ch = '\n'; break;
    // case 'r': ch = '\r'; break;
    // case 't': ch = '\t'; break;
    // case 'v': ch = '\v'; break;
    // case 'u': ch = fromHex(beg, end, 4); break;
    // case 'U': ch = fromHex(beg, end, 8); break;
    // case 'x': ch = fromHex(beg, end, 2); break;
    // default: break;
    // }

    // return std::make_pair(ch, true);
}

}}

#endif
