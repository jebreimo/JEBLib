#include "Utf16String.hpp"

#include "JEBString/JEBStringMacros.hpp"
#include "JEBString/EncodedStrings/EncodedString.hpp"
#include "JEBString/EncodedStrings/Utf16Encoding.hpp"
#include "JEBString/Utf8/Utf8Utilities.hpp"

namespace JEBString { namespace Utf16 {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::Utf16Encoding;

std::wstring& append(std::wstring& str, uint32_t chr)
{
    EncodedStrings::addUtf16(std::back_inserter(str), chr);
    return str;
}

int32_t caseInsensitiveCompare(const std::wstring& str, const std::wstring& cmp)
{
    return EncodedStrings::caseInsensitiveCompare(utf16Range(str), utf16Range(cmp));
}

bool caseInsensitiveEqual(const std::wstring& str, const std::wstring& cmp)
{
    return EncodedStrings::caseInsensitiveEqual(utf16Range(str), utf16Range(str));
}

bool caseInsensitiveLess(const std::wstring& str, const std::wstring& cmp)
{
    return EncodedStrings::caseInsensitiveLess(utf16Range(str), utf16Range(cmp));
}

bool contains(const std::wstring& str, uint32_t chr)
{
    return EncodedStrings::contains(utf16Range(str), chr);
}

bool endsWith(const std::wstring& str,
              const std::wstring& cmp,
              FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return EncodedStrings::endsWith(utf16Range(str), utf16Range(cmp), flags);
}

StringRange findSubstring(const std::wstring& str,
                          const std::wstring& sub,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf16Range(str), utf16Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

MutableStringRange findSubstring(std::wstring& str,
                                 const std::wstring& sub,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf16Range(str), utf16Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

StringRange findSubstring(StringRange str,
                          const std::wstring& sub,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf16Range(str.first, str.second),
                           utf16Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

MutableStringRange findSubstring(MutableStringRange str,
                                 const std::wstring& sub,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf16Range(str.first, str.second),
                           utf16Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

std::wstring insert(const std::wstring& str, ptrdiff_t pos,
                   const std::wstring& sub)
{
    auto it = nthCharacter(str, pos);
    std::wstring result(begin(str), it);
    result.append(sub);
    result.append(it, end(str));
    return result;
}

std::wstring insert(const std::wstring& str, ptrdiff_t pos, uint32_t chr)
{
    auto it = nthCharacter(str, pos);
    std::wstring result(begin(str), it);
    append(result, chr);
    result.append(it, end(str));
    return result;
}

std::wstring& insertInPlace(std::wstring& str, ptrdiff_t pos,
                           const std::wstring& sub)
{
    str.insert(nthCharacter(str, pos), begin(sub), end(sub));
    return str;
}

bool isAlphaNumeric(const std::wstring& str)
{
    return isAlphaNumeric(begin(str), end(str));
}

// bool isValidUtf16(const std::wstring& str)
// {
//     return EncodedStrings::isValidUtf16(begin(str), end(str));
// }

std::wstring lower(const std::wstring& str)
{
    std::wstring result;
    result.reserve(str.size());
    EncodedStrings::forEachLower(
            utf16Range(str),
            [&](uint32_t c) {EncodedStrings::addUtf16(back_inserter(result), c);});
    return result;
}

std::wstring::iterator nthCharacter(std::wstring& str, ptrdiff_t n)
{
    return EncodedStrings::nthCharacter(utf16Range(str), n);
}

std::wstring::const_iterator nthCharacter(const std::wstring& str, ptrdiff_t n)
{
    return EncodedStrings::nthCharacter(utf16Range(str), n);
}

std::wstring replace(const std::wstring& str,
                    ptrdiff_t first,
                    ptrdiff_t last,
                    const std::wstring& repl)
{
    auto strRange = utf16Range(str);
    auto fIt = EncodedStrings::nthCharacter(strRange, first);
    auto lIt = EncodedStrings::nthCharacter(strRange, last);
    std::wstring result(begin(str), fIt);
    result.append(repl);
    return result.append(lIt, end(str));
}

std::wstring replace(const std::wstring& str,
                    const std::wstring& cmp,
                    const std::wstring& subst,
                    size_t max,
                    FindFlags_t flags)
{
    std::wstring result;
    return EncodedStrings::replace(result, utf16Range(str), utf16Range(cmp),
                            utf16Range(subst), max, flags);
}

std::wstring replaceCodePoint(const std::wstring& s,
                             uint32_t fromChar,
                             uint32_t toChar,
                             size_t max)
{
    wchar_t fromBuffer[2];
    auto fromEnd = std::begin(fromBuffer);
    EncodedStrings::encodeUtf16(fromEnd, std::end(fromBuffer), fromChar);
    wchar_t toBuffer[2];
    auto toEnd = std::begin(toBuffer);
    EncodedStrings::encodeUtf16(toEnd, std::end(toBuffer), toChar);
    std::wstring result;
    EncodedStrings::replace(result, utf16Range(s),
                     utf16Range(fromBuffer, fromEnd),
                     utf16Range(toBuffer, toEnd),
                     max, FindFlags::Defaults);
    return result;
}

std::wstring& replaceInPlace(std::wstring& str,
                            ptrdiff_t first,
                            ptrdiff_t last,
                            const std::wstring& repl)
{
    auto strRange = utf16Range(str);
    auto fIt = EncodedStrings::nthCharacter(strRange, first);
    auto lIt = EncodedStrings::nthCharacter(strRange, last);
    return str.replace(fIt, lIt, repl);
}

std::wstring replaceInvalidUtf16(const std::wstring& str, uint32_t chr)
{
    std::wstring result;
    result.reserve(str.size());
    auto beg = str.begin();
    auto it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (EncodedStrings::nextUtf16CodePoint(cp, it, str.end())
                != DecodeResult::Ok)
        {
            result.append(beg, it);
            beg = ++it;
            append(result, chr);
        }
    }
    result.append(beg, str.end());
    return result;
}

std::wstring& replaceInvalidUtf16InPlace(std::wstring& str, char chr)
{
    assert(chr > 0);
    auto it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (EncodedStrings::nextUtf16CodePoint(cp, it, str.end())
                != DecodeResult::Ok)
            *it++ = chr;
    }
    return str;
}

std::wstring reverse(const std::wstring& str)
{
    std::wstring result;
    result.reserve(str.size());
    EncodedStrings::reverse(utf16Range(str), utf16Encoder(result));
    return result;
}

std::vector<std::wstring> split(
        const std::wstring& str,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::IgnoreEmpty*/)
{
    std::vector<std::wstring> parts;
    EncodedStrings::forEachToken(utf16Range(str), Unicode::isWhitespace,
                          rangePushBacker(parts), maxParts, flags);
    return parts;
}

std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& sep,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::wstring> parts;
    EncodedStrings::forEachToken(utf16Range(str), utf16Range(sep),
                          rangePushBacker(parts), maxParts, flags);
    return parts;
}

std::vector<std::wstring> splitLines(
        const std::wstring& str,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::wstring> parts;
    EncodedStrings::forEachLine(utf16Range(str), rangePushBacker(parts),
                         maxParts, flags);
    return parts;
}

bool startsWith(const std::wstring& str,
                const std::wstring& cmp,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return EncodedStrings::startsWith(utf16Range(str), utf16Range(cmp), flags);
}

size_t stringLength(const std::wstring& str)
{
    return stringLength(begin(str), end(str));
}

std::wstring substring(
        const std::wstring& str,
        ptrdiff_t startIndex,
        ptrdiff_t endIndex /*= std::numeric_limits<ptrdiff_t>::max()*/)
{
    return toString(EncodedStrings::substring(utf16Range(str),
                                       startIndex, endIndex));
}

std::wstring title(const std::wstring& str)
{
    std::wstring result;
    result.reserve(str.size());
    EncodedStrings::forEachTitle(
            utf16Range(str),
            [&](uint32_t c) {EncodedStrings::addUtf16(back_inserter(result), c);});
    return result;
}

std::wstring toString(uint32_t chr)
{
    std::wstring result;
    EncodedStrings::addUtf16(back_inserter(result), chr);
    return result;
}

std::wstring toUtf16(const std::string& str, Encoding_t encoding)
{
    std::wstring result;
    result.reserve(str.size());
    switch (encoding)
    {
    case Encoding::Utf8:
        EncodedStrings::copy(Utf8::utf8Range(str), utf16Encoder(result));
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to UTF-16: unsupported encoding "
                              << encoding << "."));
    }
    return result;
}

std::wstring toUtf16(const std::wstring& str,
                   Encoding_t encoding /*= Encoding::Utf16*/)
{
    std::wstring result;
    result.reserve(str.size());
    switch (encoding)
    {
    case Encoding::Utf16:
        EncodedStrings::copy(utf16Range(str), utf16Encoder(result));
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to UTF-16: unsupported encoding "
                              << encoding << "."));
    }
    return result;
}

std::wstring trim(const std::wstring& str)
{
    return toString(EncodedStrings::trim(utf16Range(str), Unicode::isWhitespace));
}

std::wstring trimFront(const std::wstring& str)
{
    return toString(EncodedStrings::trimFront(utf16Range(str),
                                       Unicode::isWhitespace));
}

std::wstring trimBack(const std::wstring& str)
{
    return toString(EncodedStrings::trimBack(utf16Range(str),
                                      Unicode::isWhitespace));
}

std::wstring upper(const std::wstring& str)
{
    std::wstring result;
    result.reserve(str.size());
    EncodedStrings::forEachUpper(
            utf16Range(str),
            [&](uint32_t c) {EncodedStrings::addUtf16(back_inserter(result), c);});
    return result;
}

}}
