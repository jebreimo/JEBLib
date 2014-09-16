#include "JEBString/Unicode/CaseInsensitive.hpp"
#include "JEBString/Unicode/UnicodePredicates.hpp"
#include "CodePointAlgorithms.hpp"

namespace JEBString { namespace CodePoints {

namespace detail
{
    template <typename Decoder, typename UnaryFunc1, typename UnaryFunc2>
    CodePointIterator<Decoder> forEachToken_impl(
            CodePointIterator<Decoder> str,
            UnaryFunc1 nextTokenFunc,
            UnaryFunc2 tokenFunc, size_t maxParts,
            SplitFlags_t flags);
}

template <typename Decoder>
bool advanceCharacter(CodePointIterator<Decoder>& it)
{
    uint32_t ch;
    if (!it.next(ch))
        return false;
    auto prevIt = it.internalBegin();
    if (CodePointIterator<Decoder>::Forward)
    {
        while (it.next(ch))
        {
            if (!Unicode::isMark(ch))
            {
                it.setInternalBegin(prevIt);
                break;
            }
            prevIt = it.internalBegin();
        }
    }
    else
    {
        while (Unicode::isMark(ch) && it.next(ch))
        {}
    }
    return true;
}

template <typename Decoder>
size_t advanceCharacters(CodePointIterator<Decoder>& it, size_t n)
{
    for (size_t i = 0; i != n; ++i)
    {
        if (!advanceCharacter(it))
            return i;
    }
    return n;
}

template <typename Decoder1, typename Decoder2>
int32_t caseInsensitiveCompare(CodePointIterator<Decoder1> str,
                               CodePointIterator<Decoder2> cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (empty(str) && empty(cmp))
        return 0;
    else if (empty(str))
        return -1;
    else if (empty(cmp))
        return 1;
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveCompare(strCh, cmpCh);
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveEqual(CodePointIterator<Decoder1> str,
                          CodePointIterator<Decoder2> cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    return empty(str) && empty(cmp);
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveLess(CodePointIterator<Decoder1> str,
                         CodePointIterator<Decoder2> cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (empty(str) || empty(cmp))
        return empty(str) && !empty(cmp);
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveLess(strCh, cmpCh);
}

template <typename Decoder, typename OutIt, typename Enc>
void copy(CodePointIterator<Decoder> str,
          EncodedStrings::Encoder<OutIt, Enc> encoder)
{
    uint32_t c;
    while (str.next(c))
        encoder.encode(c);
}

template <typename Decoder1, typename Decoder2>
CodePointIterator<Decoder1> find(CodePointIterator<Decoder1>& str,
                                 CodePointIterator<Decoder2> sub,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        return search(str, sub, Unicode::CaseInsensitiveEqual());
    else
        return search(str, sub);
}

template <typename Decoder, typename UnaryFunc>
CodePointIterator<Decoder> forEachLine(
        CodePointIterator<Decoder> str,
        UnaryFunc tokenFunc, size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return detail::forEachToken_impl(
            str,
            [&](CodePointIterator<Decoder>& s) {return nextLine(s);},
            tokenFunc, maxParts, flags);
}

template <typename Decoder, typename UnaryPred, typename UnaryFunc>
CodePointIterator<Decoder> forEachToken(
        CodePointIterator<Decoder> str, UnaryPred delimiterPred,
        UnaryFunc tokenFunc, size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return detail::forEachToken_impl(
            str,
            [&](CodePointIterator<Decoder>& s)
                {return nextToken(s, delimiterPred);},
            tokenFunc, maxParts, flags);
}

template <typename Decoder1, typename Decoder2, typename UnaryFunc>
CodePointIterator<Decoder1> forEachToken(
        CodePointIterator<Decoder1> str,
        CodePointIterator<Decoder2> delimiter,
        UnaryFunc tokenFunc, size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    auto fflags = SplitFlags::caseInsensitive(flags)
                ? FindFlags::CaseInsensitive
                : FindFlags::Defaults;
    return detail::forEachToken_impl(
            str,
            [&](CodePointIterator<Decoder1>& s)
                {return nextToken(s, delimiter, fflags);},
            tokenFunc, maxParts, flags);
}

template <typename Decoder>
CodePointIterator<Decoder> nextLine(CodePointIterator<Decoder>& str)
{
    auto line = str;
    auto newline = nextNewline(str);
    line.setInternalEnd(newline.internalBegin());
    return line;
}

template <typename Decoder>
CodePointIterator<Decoder> nextNewline(CodePointIterator<Decoder>& str)
{
    auto newline = str;
    uint32_t ch;
    while (str.next(ch))
    {
        switch (ch)
        {
        case '\n':
            if (!CodePointIterator<Decoder>::Forward)
            {
                auto copyOfStr = str;
                if (str.next(ch) && ch != '\r')
                    str.setInternalBegin(copyOfStr.internalBegin());
            }
            newline.setInternalEnd(str.internalBegin());
            return newline;
        case '\v':
        case '\f':
        case Unicode::NextLine:
        case Unicode::LineSeparator:
        case Unicode::ParagraphSeparator:
            newline.setInternalEnd(str.internalBegin());
            return newline;
        case '\r':
            if (CodePointIterator<Decoder>::Forward)
            {
                auto copyOfStr = str;
                if (str.next(ch) && ch != '\n')
                    str.setInternalBegin(copyOfStr.internalBegin());
            }
            newline.setInternalEnd(str.internalBegin());
            return newline;
        default:
            break;
        }
        newline.setInternalBegin(str.internalBegin());
    }
    return str;
}

template <typename Decoder, typename UnaryPred>
CodePointIterator<Decoder> nextToken(CodePointIterator<Decoder>& str,
                                     UnaryPred pred)
{
    auto token = str;
    token.setInternalEnd(str.internalBegin());
    uint32_t ch;
    while (str.next(ch) && !pred(ch))
        token.setInternalEnd(str.internalBegin());
    return token;
}

template <typename Decoder1, typename Decoder2>
CodePointIterator<Decoder1> nextToken(
        CodePointIterator<Decoder1>& str,
        CodePointIterator<Decoder2> cmp,
        FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto token = str;
    auto delimiter = JEBString::CodePoints::find(str, cmp, flags);
    token.setInternalEnd(delimiter.internalBegin());
    return token;
}

template <typename Decoder1, typename Decoder2>
bool startsWith(CodePointIterator<Decoder1> str,
                CodePointIterator<Decoder2> cmp,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    if (FindFlags::caseInsensitive(flags))
        advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    else
        advanceWhileEqual(str, cmp);
    return empty(cmp);
}

namespace detail
{
    template <typename Decoder, typename UnaryFunc1, typename UnaryFunc2>
    CodePointIterator<Decoder> forEachToken_impl(
            CodePointIterator<Decoder> str, UnaryFunc1 nextTokenFunc,
            UnaryFunc2 tokenFunc, size_t maxParts,
            SplitFlags_t flags)
    {
        while (maxParts != 1 && !empty(str))
        {
            auto token = nextTokenFunc(str);
            if (!SplitFlags::ignoreEmpty(flags) || !empty(token))
            {
                tokenFunc(makeEncodedRange(token));
                --maxParts;
            }
            if (end(token) == end(str))
                return str;
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmpty(flags) || !empty(str)))
        {
            tokenFunc(makeEncodedRange(str));
        }
        return str;
    }
}

}}
