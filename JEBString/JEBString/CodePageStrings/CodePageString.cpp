#include "CodePageString.hpp"

#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include "JEBString/JEBStringMacros.hpp"
#include "JEBString/EncodedStrings/EncodedString.hpp"
#include "JEBString/EncodedStrings/Encoder.hpp"
#include "JEBString/Unicode/CaseConverter.hpp"
#include "JEBString/Unicode/CaseInsensitive.hpp"
#include "JEBString/Unicode/UnicodePredicates.hpp"
#include "JEBString/Utf8/Utf8Utilities.hpp"
#include "JEBString/Utf16/Utf16Utilities.hpp"

namespace JEBString { namespace CodePageStrings {

using JEBBase::Ranges::makeRange;
using JEBBase::Ranges::makeReverseIterator;
// using JEBBase::Ranges::makeReverseRange;

namespace detail {

    struct Compare
    {
        Compare(const CodePage& codePage) : codePage(codePage)
        {}

        int32_t operator()(char a, char b)
        {
            return Unicode::caseInsensitiveCompare(codePage.toCodePoint(a),
                                                   codePage.toCodePoint(b));
        }
        const CodePage& codePage;
    };

    struct Equal
    {
        Equal(const CodePage& codePage) : codePage(codePage)
        {}

        int32_t operator()(char a, char b)
        {
            return Unicode::caseInsensitiveEqual(codePage.toCodePoint(a),
                                                 codePage.toCodePoint(b));
        }
        const CodePage& codePage;
    };

    struct Less
    {
        Less(const CodePage& codePage) : codePage(codePage)
        {}

        int32_t operator()(char a, char b)
        {
            return Unicode::caseInsensitiveLess(codePage.toCodePoint(a),
                                                codePage.toCodePoint(b));
        }
        const CodePage& codePage;
    };

    template <typename UnaryFunc, typename StringRange>
    StringRange forEachToken(const CodePage& codePage,
                             StringRange str, const std::string& delimiter,
                             UnaryFunc tokenFunc, size_t maxParts /*= 0*/,
                             SplitFlags_t flags /*= SplitFlags::Defaults*/)
    {
        auto fflags = SplitFlags::caseInsensitive(flags) ?
                      FindFlags::CaseInsensitive :
                      FindFlags::Defaults;
        while (maxParts != 1 && str.first != str.second)
        {
            auto token = nextToken(codePage, str, delimiter, fflags);
            if (!SplitFlags::ignoreEmpty(flags) ||
                token.first != token.second)
            {
                tokenFunc(token);
                --maxParts;
            }
            if (token.second == str.second)
                return str;
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmpty(flags) || str.first != str.second))
        {
            tokenFunc(str);
            str.first = str.second;
        }
        return str;
    }

    char toCharacter(uint32_t c, char unsupportedCodePointChar)
    {
        if (c >= 256)
            return unsupportedCodePointChar;
        return static_cast<char>(c);
    }

    template <typename It, typename Enc>
    std::string toString(CodePoints::EncodedRange<It, Enc> str,
                         const CodePage& codePage,
                         char unsupportedCodePointChar)
    {
        std::string result;
        EncodedStrings::forEachCodePoint(str,
                [&](uint32_t c)
                {result.push_back(toCharacter(codePage.fromCodePoint(c),
                                              unsupportedCodePointChar));});
        return result;
    }

    std::string toString(std::string str,
                         const CodePage& fromCodePage,
                         const CodePage& toCodePage,
                         char unsupportedCodePointChar)
    {
        for (auto it = begin(str); it != end(str); ++it)
        {
            auto cp = fromCodePage.toCodePoint(*it);
            *it = toCharacter(toCodePage.fromCodePoint(cp),
                              unsupportedCodePointChar);
        }
        return str;
    }
}

int32_t caseInsensitiveCompare(const CodePage& codePage,
                               const std::string& str,
                               const std::string& cmp)
{
    return JEBBase::Ranges::compare(
            makeRange(str), makeRange(cmp), detail::Compare(codePage));
}

bool caseInsensitiveEqual(const CodePage& codePage,
                          const std::string& str,
                          const std::string& cmp)
{
    return JEBBase::Ranges::equal(
            makeRange(str), makeRange(cmp), detail::Equal(codePage));
}

bool caseInsensitiveLess(const CodePage& codePage,
                         const std::string& str,
                         const std::string& cmp)
{
    return JEBBase::Ranges::less(
            makeRange(str), makeRange(cmp),
            detail::Equal(codePage), detail::Less(codePage));
}

bool endsWith(const CodePage& codePage,
              const std::string& str,
              const std::string& cmp,
              FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        return JEBBase::Algorithms::mismatch(
                str.rbegin(), str.rend(), cmp.rbegin(), cmp.rend(),
                detail::Equal(codePage)).second == cmp.rend();
    else
        return JEBBase::Algorithms::mismatch(
                str.rbegin(), str.rend(), cmp.rbegin(), cmp.rend()
               ).second == cmp.rend();
}

StringRange findSubstring(const CodePage& codePage,
                          const std::string& str,
                          const std::string& cmp,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return findSubstring(codePage, StringRange(begin(str), end(str)),
                         cmp, flags);
}

MutableStringRange findSubstring(const CodePage& codePage,
                                 std::string& str,
                                 const std::string& cmp,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return findSubstring(codePage, MutableStringRange(begin(str), end(str)),
                         cmp, flags);
}

StringRange findSubstring(const CodePage& codePage,
                          StringRange str,
                          const std::string& cmp,
                          FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        return search(makeRange(str), makeRange(cmp),
                      detail::Equal(codePage));
    else
        return search(makeRange(str), makeRange(cmp));
}

MutableStringRange findSubstring(const CodePage& codePage,
                                 MutableStringRange str,
                                 const std::string& cmp,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        return search(makeRange(str), makeRange(cmp),
                      detail::Equal(codePage));
    else
        return search(makeRange(str), makeRange(cmp));
}

std::string lower(const CodePage& codePage, const std::string& str)
{
    auto result = str;
    return toLower(codePage, result);
}

StringRange nextToken(const CodePage& codePage,
                      StringRange& str,
                      const std::string& delimiter,
                      FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto match = findSubstring(codePage, str, delimiter, flags);
    StringRange result(str.first, match.first);
    str.first = match.second;
    return result;
}

std::string replace(const CodePage& codePage,
                    const std::string& str,
                    const std::string& from,
                    const std::string& to,
                    size_t max /*= 0*/,
                    FindFlags_t flags /*= FindFlags::Defaults*/)
{
    std::string result;
    auto start = begin(str);
    auto match = findSubstring(codePage, str, from, flags);
    while (match.first != end(str))
    {
        result.append(start, match.first);
        result.append(to);
        start = match.second;
        if (--max == 0)
            break;
        match = findSubstring(codePage, make_pair(start, end(str)), from,
                              flags);
    }
    result.append(start, end(str));
    return result;
}

std::vector<std::string> split(
        const CodePage& codePage,
        const std::string& str,
        const std::string& sep,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::string> result;
    detail::forEachToken(
        codePage, std::make_pair(begin(str), end(str)), sep,
        [&](StringRange r){result.push_back(std::string(r.first, r.second));},
        maxParts, flags);
    return result;
}

bool startsWith(const CodePage& codePage,
                const std::string& str,
                const std::string& cmp,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        return JEBBase::Algorithms::mismatch(
                begin(str), end(str), begin(cmp), end(cmp),
                detail::Equal(codePage)).second == end(cmp);
    else
        return JEBBase::Algorithms::mismatch(
                begin(str), end(str), begin(cmp), end(cmp)
               ).second == end(cmp);
}

std::string title(const CodePage& codePage, const std::string& str)
{
    auto result = str;
    return toTitle(codePage, result);
}

std::string& toLower(const CodePage& codePage, std::string& str)
{
    for (auto it = begin(str); it != end(str); ++it)
    {
        auto ch = codePage.toCodePoint(*it);
        auto lo = codePage.fromCodePoint(Unicode::lower(ch));
        if (lo < 256)
            *it = static_cast<char>(lo);
    }
    return str;
}

std::string toCodePageString(const CodePage& codePage, const std::string str,
                             Encoding_t encoding,
                             char unsupportedCodePointChar /*= '?'*/)
{
    if (encoding == codePage.encoding())
        return str;

    switch (encoding)
    {
    case Encoding::Utf8:
        return detail::toString(Utf8::utf8Range(str), codePage,
                                unsupportedCodePointChar);
        break;
    case Encoding::Latin1:
    case Encoding::Windows1252:
        detail::toString(str, CodePageStrings::codePage(encoding), codePage,
                         unsupportedCodePointChar);
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to codepage: unsupported encoding "
                              << encoding << "."));
        break;
    }
    return std::string();
}

std::string toCodePageString(const CodePage& codePage, const std::wstring str,
                             Encoding_t encoding,
                             char unsupportedCodePointChar /*= '?'*/)
{
    switch (encoding)
    {
    case Encoding::Utf16:
        return detail::toString(Utf16::utf16Range(str), codePage,
                                unsupportedCodePointChar);
        break;
    default:
        throw std::logic_error(
                FORMAT_STRING("Convert to codepage: unsupported encoding "
                              << encoding << "."));
        break;
    }
    return std::string();
}

std::string& toTitle(const CodePage& codePage, std::string& str)
{
    bool capNext = true;
    for (auto it = begin(str); it != end(str); ++it)
    {
        auto ch = codePage.toCodePoint(*it);
        auto lo = ch;
        if (!Unicode::isCasedLetter(ch))
        {
            capNext = !Unicode::isLetter(ch);
        }
        else if (capNext)
        {
            lo = Unicode::title(ch);
            capNext = false;
        }
        else
        {
            lo = Unicode::lower(ch);
        }
        if (lo < 256)
            *it = static_cast<char>(lo);
    }
    return str;
}

std::string& toUpper(const CodePage& codePage, std::string& str)
{
    for (auto it = begin(str); it != end(str); ++it)
    {
        auto ch = codePage.toCodePoint(*it);
        auto lo = codePage.fromCodePoint(Unicode::upper(ch));
        if (lo < 256)
            *it = static_cast<char>(lo);
    }
    return str;
}

std::string upper(const CodePage& codePage, const std::string& str)
{
    auto result = str;
    return toUpper(codePage, result);
}

}}
