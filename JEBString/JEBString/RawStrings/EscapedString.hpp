#ifndef JEBSTRING_RAWSTRINGS_ESCAPEDRAWSTRING_HPP
#define JEBSTRING_RAWSTRINGS_ESCAPEDRAWSTRING_HPP

#include <cstdint>
#include <type_traits>

namespace JEBString { namespace RawStrings {

template <typename FwdIt>
uint32_t fromHex(FwdIt& first, FwdIt last, size_t length)
{
    uint32_t ch = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (first == last)
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        uint32_t tmp = *first;
        ch *= 16;
        if ('0' <= tmp && tmp <= '9')
            ch += tmp - '0';
        else if ('A' <= tmp && tmp <= 'F')
            ch += tmp - 'A' + 10;
        else if ('a' <= tmp && tmp <= 'f')
            ch += tmp - 'a' + 10;
        else
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        ++first;
    }
    return ch;
}

template <typename FwdIt>
bool unescapeNext(FwdIt& first, FwdIt last, uint32_t& chr, bool& escaped,
                  uint32_t escapeChar = '\\')
{
    escaped = false;
    if (first == last)
    {
        chr = ~(uint32_t)0;
        return false;
    }
    chr = *first;
    ++first;

    if (chr != escapeChar)
        return true;

    if (first == last)
        throw std::invalid_argument("Invalid escaped character.");

    escaped = true;
    chr = *first;
    ++first;
    switch (chr)
    {
    case '0': chr = '\0'; break;
    case 'U': chr = fromHex(first, last, 8); break;
    case 'a': chr = '\a'; break;
    case 'b': chr = '\b'; break;
    case 'f': chr = '\f'; break;
    case 'n': chr = '\n'; break;
    case 'r': chr = '\r'; break;
    case 't': chr = '\t'; break;
    case 'v': chr = '\v'; break;
    case 'u': chr = fromHex(first, last, 4); break;
    case 'x': chr = fromHex(first, last, 2); break;
    default: break;
    }

    return true;
}

template <typename FwdIt>
std::pair<uint32_t, bool> unescapeNext(FwdIt& first, FwdIt last,
                                       uint32_t escapeChar = '\\')
{
    std::pair<uint32_t, bool> result;
    unescapeNext(first, last, result.first, result.second, escapeChar);
    return result;
}

template <typename String, typename EncodeFunc>
String unescapeString(const String& str, EncodeFunc encodeFunc,
                      uint32_t escapeChar = '\\')
{
    String result;
    auto first = begin(str);
    auto last = std::find(first, end(str), '\\');
    while (last != end(str))
    {
        result.insert(end(result), first, last);
        auto chr = unescapeNext(last, end(str), escapeChar);
        encodeFunc(result, chr.first);
        first = last;
        last = std::find(first, end(str), '\\');
    }
    result.insert(end(result), first, last);
    return result;
}

inline uint8_t chrToDigit(uint8_t c)
{
    return c + (c < 0xA ? '0' : 'A' - 10);
}

template <typename String>
void escapeCharacter(String& dst, uint32_t chr)
{
    dst.push_back('\\');
    switch (chr)
    {
    case '\0': dst.push_back('0'); break;
    case '\a': dst.push_back('a'); break;
    case '\b': dst.push_back('b'); break;
    case '\f': dst.push_back('f'); break;
    case '\n': dst.push_back('n'); break;
    case '\r': dst.push_back('r'); break;
    case '\t': dst.push_back('t'); break;
    case '\v': dst.push_back('v'); break;
    default:
        {
            auto shift = 8;
            if (chr < 256)
            {
                dst.push_back('x');
            }
            else if (chr < 0x10000)
            {
                dst.push_back('u');
                shift = 16;
            }
            else
            {
                dst.push_back('U');
                shift = 32;
            }
            for (; shift != 0; shift -= 4)
                dst.push_back(chrToDigit((chr >> (shift - 4)) & 0xF));
        }
        break;
    }
}

bool isSingleByteControlChar(uint32_t c)
{
    return c < 32 || (127 <= c && c < 160);
}

template <typename String>
String escapeControlCharacters(const String& s)
{
    String result;
    typedef typename std::make_unsigned<typename String::value_type>::type
            CharType;
    auto escape = [](CharType c)
                    {return c < 32 || (127 <= c && c < 160);};
    auto first = begin(s);
    auto last = std::find_if(first, end(s), escape);
    while (last != end(s))
    {
        result.insert(end(result), first, last);
        escapeCharacter(result, (CharType)*last);
        first = ++last;
        last = std::find_if(first, end(s), escape);
    }
    result.insert(end(result), first, end(s));
    return result;
}

}}

#endif
