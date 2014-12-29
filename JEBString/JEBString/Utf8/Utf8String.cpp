#include "Utf8String.hpp"

#include "JEBString/JEBStringMacros.hpp"
#include "JEBString/EncodedStrings/EncodedString.hpp"
#include "JEBString/EncodedStrings/CodePageEncoding.hpp"
#include "JEBString/EncodedStrings/Utf8Encoding.hpp"
#include "JEBString/RawStrings/EscapedString.hpp"
#include "JEBString/Utf16/Utf16Utilities.hpp"

namespace JEBString { namespace Utf8 {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::Utf8Encoding;

std::string& append(std::string& str, uint32_t chr)
{
    EncodedStrings::addUtf8(std::back_inserter(str), chr);
    return str;
}

int32_t caseInsensitiveCompare(const std::string& str, const std::string& cmp)
{
    return EncodedStrings::caseInsensitiveCompare(utf8Range(str),
                                                  utf8Range(cmp));
}

bool caseInsensitiveEqual(const std::string& str, const std::string& cmp)
{
    return EncodedStrings::caseInsensitiveEqual(utf8Range(str),
                                                utf8Range(cmp));
}

bool caseInsensitiveLess(const std::string& str, const std::string& cmp)
{
    return EncodedStrings::caseInsensitiveLess(utf8Range(str),
                                               utf8Range(cmp));
}

bool contains(const std::string& str, uint32_t chr)
{
    return EncodedStrings::contains(utf8Range(str), chr);
}

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return EncodedStrings::endsWith(utf8Range(str), utf8Range(cmp), flags);
}

std::string escape(const std::string& str)
{
    return RawStrings::escapeControlCharacters(str);
}

StringRange findSubstring(const std::string& str,
                          const std::string& sub,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf8Range(str), utf8Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

MutableStringRange findSubstring(std::string& str,
                                 const std::string& sub,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf8Range(str), utf8Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

StringRange findSubstring(StringRange str,
                          const std::string& sub,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf8Range(str.first, str.second),
                           utf8Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

MutableStringRange findSubstring(MutableStringRange str,
                                 const std::string& sub,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto r = EncodedStrings::find(utf8Range(str.first, str.second),
                           utf8Range(sub), flags);
    return std::make_pair(begin(r), end(r));
}

std::string insert(const std::string& str, ptrdiff_t pos,
                   const std::string& sub)
{
    auto it = nthCharacter(str, pos);
    std::string result(begin(str), it);
    result.append(sub);
    result.append(it, end(str));
    return result;
}

std::string insert(const std::string& str, ptrdiff_t pos, uint32_t chr)
{
    auto it = nthCharacter(str, pos);
    std::string result(begin(str), it);
    append(result, chr);
    result.append(it, end(str));
    return result;
}

std::string& insertInPlace(std::string& str, ptrdiff_t pos,
                           const std::string& sub)
{
    str.insert(nthCharacter(str, pos), begin(sub), end(sub));
    return str;
}

bool isAlphaNumeric(const std::string& str)
{
    return isAlphaNumeric(begin(str), end(str));
}

bool isValidUtf8(const std::string& str)
{
    return EncodedStrings::isValidUtf8(begin(str), end(str));
}

std::string lower(const std::string& str)
{
    std::string result;
    result.reserve(str.size());
    EncodedStrings::forEachLower(
            utf8Range(str),
            [&](uint32_t c)
               {EncodedStrings::addUtf8(back_inserter(result), c);});
    return result;
}

std::string::iterator nthCharacter(std::string& str, ptrdiff_t n)
{
    return EncodedStrings::nthCharacter(utf8Range(str), n);
}

std::string::const_iterator nthCharacter(const std::string& str, ptrdiff_t n)
{
    return EncodedStrings::nthCharacter(utf8Range(str), n);
}

std::string replace(const std::string& str,
                    ptrdiff_t first,
                    ptrdiff_t last,
                    const std::string& repl)
{
    auto strRange = utf8Range(str);
    auto fIt = EncodedStrings::nthCharacter(strRange, first);
    auto lIt = EncodedStrings::nthCharacter(strRange, last);
    std::string result(begin(str), fIt);
    result.append(repl);
    return result.append(lIt, end(str));
}

std::string replace(const std::string& str,
                    const std::string& cmp,
                    const std::string& subst,
                    size_t max,
                    FindFlags_t flags)
{
    std::string result;
    return EncodedStrings::replace(result, utf8Range(str), utf8Range(cmp),
                            utf8Range(subst), max, flags);
}

std::string replaceCodePoint(const std::string& s,
                             uint32_t fromChar,
                             uint32_t toChar,
                             size_t max)
{
    char fromBuffer[EncodedStrings::MAX_ENCODED_UTF8_LENGTH];
    size_t fromSize = EncodedStrings::encodeUtf8(fromBuffer, fromChar);
    char toBuffer[EncodedStrings::MAX_ENCODED_UTF8_LENGTH];
    auto toSize = EncodedStrings::encodeUtf8(toBuffer, toChar);
    std::string result;
    EncodedStrings::replace(result, utf8Range(s),
                     utf8Range(fromBuffer, fromBuffer + fromSize),
                     utf8Range(toBuffer, toBuffer + toSize),
                     max, FindFlags::Defaults);
    return result;
}

std::string& replaceInPlace(std::string& str,
                            ptrdiff_t first,
                            ptrdiff_t last,
                            const std::string& repl)
{
    auto strRange = utf8Range(str);
    auto fIt = EncodedStrings::nthCharacter(strRange, first);
    auto lIt = EncodedStrings::nthCharacter(strRange, last);
    return str.replace(fIt, lIt, repl);
}

std::string replaceInvalidUtf8(const std::string& str, uint32_t chr)
{
    std::string result;
    result.reserve(str.size());
    auto beg = str.begin();
    auto it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (EncodedStrings::nextUtf8CodePoint(cp, it, str.end())
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

std::string& replaceInvalidUtf8InPlace(std::string& str, char chr)
{
    assert(chr > 0);
    auto it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (EncodedStrings::nextUtf8CodePoint(cp, it, str.end())
                != DecodeResult::Ok)
            *it++ = chr;
    }
    return str;
}

std::string reverse(const std::string& str)
{
    std::string result;
    result.reserve(str.size());
    EncodedStrings::reverse(utf8Range(str), utf8Encoder(result));
    return result;
}

std::vector<std::string> split(
        const std::string& str,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::IgnoreEmpty*/)
{
    std::vector<std::string> parts;
    EncodedStrings::forEachToken(utf8Range(str), Unicode::isWhitespace,
                          rangePushBacker(parts), maxParts, flags);
    return parts;
}

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::string> parts;
    EncodedStrings::forEachToken(utf8Range(str), utf8Range(sep),
                          rangePushBacker(parts), maxParts, flags);
    return parts;
}

std::vector<std::string> splitLines(
        const std::string& str,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::string> parts;
    EncodedStrings::forEachLine(utf8Range(str), rangePushBacker(parts),
                         maxParts, flags);
    return parts;
}

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return EncodedStrings::startsWith(utf8Range(str), utf8Range(cmp), flags);
}

size_t stringLength(const std::string& str)
{
    return stringLength(begin(str), end(str));
}

std::string substring(
        const std::string& str,
        ptrdiff_t startIndex,
        ptrdiff_t endIndex /*= std::numeric_limits<ptrdiff_t>::max()*/)
{
    return toString(EncodedStrings::substring(utf8Range(str),
                                       startIndex, endIndex));
}

std::string title(const std::string& str)
{
    std::string result;
    result.reserve(str.size());
    EncodedStrings::forEachTitle(
            utf8Range(str),
            [&](uint32_t c) {EncodedStrings::addUtf8(back_inserter(result), c);});
    return result;
}

std::string toString(uint32_t chr)
{
    char buffer[EncodedStrings::MAX_ENCODED_UTF8_LENGTH];
    size_t n = EncodedStrings::encodeUtf8(buffer, chr);
    return std::string(buffer, buffer + n);
}

std::string toUtf8(const std::string& str, Encoding_t encoding)
{
    std::string result;
    result.reserve(str.size());
    switch (encoding)
    {
    case Encoding::Utf8:
        EncodedStrings::copy(utf8Range(str), utf8Encoder(result));
        break;
    case Encoding::Latin1:
        EncodedStrings::copy(
                makeEncodedRange(str, EncodedStrings::Latin1Encoding()),
                utf8Encoder(result));
        break;
    case Encoding::Windows1252:
        EncodedStrings::copy(
                makeEncodedRange(str, EncodedStrings::Windows1252Encoding()),
                utf8Encoder(result));
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to UTF-8: unsupported encoding "
                              << encoding << "."));
    }
    return result;
}

std::string toUtf8(const std::wstring& str,
                   Encoding_t encoding /*= Encoding::Utf16*/)
{
    std::string result;
    result.reserve(str.size());
    switch (encoding)
    {
    case Encoding::Utf16:
        EncodedStrings::copy(Utf16::utf16Range(str), utf8Encoder(result));
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to UTF-8: unsupported encoding "
                              << encoding << "."));
    }
    return result;
}

std::string trim(const std::string& str)
{
    return toString(EncodedStrings::trim(utf8Range(str), Unicode::isWhitespace));
}

std::string trimFront(const std::string& str)
{
    return toString(EncodedStrings::trimFront(utf8Range(str),
                                       Unicode::isWhitespace));
}

std::string trimBack(const std::string& str)
{
    return toString(EncodedStrings::trimBack(utf8Range(str),
                                      Unicode::isWhitespace));
}

std::string unescape(const std::string& str)
{
    return RawStrings::unescapeString(str,
            [](std::string& s, uint32_t c)
                {EncodedStrings::addUtf8(back_inserter(s), c);});
}

std::string upper(const std::string& str)
{
    std::string result;
    result.reserve(str.size());
    EncodedStrings::forEachUpper(
            utf8Range(str),
            [&](uint32_t c) {EncodedStrings::addUtf8(back_inserter(result), c);});
    return result;
}

}}
