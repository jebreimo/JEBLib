#include "JEBString/CodePoints/CodePointString.hpp"

#include "JEBString/Unicode/CaseInsensitive.hpp"
#include "JEBString/Unicode/UnicodePredicates.hpp"

namespace JEBString { namespace EncodedStrings {

using CodePoints::makeForwardIterator;
using CodePoints::makeReverseIterator;

template <typename It1, typename Enc1, typename It2, typename Enc2>
int32_t caseInsensitiveCompare(EncodedRange<It1, Enc1> str,
                               EncodedRange<It2, Enc2> cmp)
{
    return caseInsensitiveCompare(makeForwardIterator(str),
                                  makeForwardIterator(cmp));
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool caseInsensitiveEqual(EncodedRange<It1, Enc1> str,
                          EncodedRange<It2, Enc2> cmp)
{
    return caseInsensitiveEqual(makeForwardIterator(str),
                                makeForwardIterator(cmp));
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool caseInsensitiveLess(EncodedRange<It1, Enc1> str,
                         EncodedRange<It2, Enc2> cmp)
{
    return caseInsensitiveLess(makeForwardIterator(str),
                               makeForwardIterator(cmp));
}

template <typename It, typename Enc>
bool contains(EncodedRange<It, Enc> str, uint32_t chr)
{
    auto it = makeForwardIterator(str);
    return advanceUntil(it, [=](uint32_t c){return c == chr;});
}

template <typename InpIt, typename Enc1, typename OutIt, typename Enc2>
void copy(EncodedRange<InpIt, Enc1> src, Encoder<OutIt, Enc2> dst)
{
    if (src.encoding().encoding == dst.encoding().encoding)
        std::copy(begin(src), end(src), dst.iterator());
    else
        copy(makeForwardIterator(src), dst);
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool endsWith(EncodedRange<It1, Enc1> str, EncodedRange<It2, Enc2> cmp,
              FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return startsWith(makeReverseIterator(str), makeReverseIterator(cmp),
                      flags);
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> find(EncodedRange<It1, Enc1> str,
                             EncodedRange<It2, Enc2> cmp,
                             FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto it = makeForwardIterator(str);
    return makeEncodedRange(CodePoints::find(
            it, makeForwardIterator(cmp), flags));
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> findNext(EncodedRange<It1, Enc1>& str,
                                 EncodedRange<It2, Enc2> cmp,
                                 FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto it = makeForwardIterator(str);
    auto result = makeEncodedRange(CodePoints::find(
            it, makeForwardIterator(cmp), flags));
    str.setBegin(end(result));
    return result;
}

template <typename It, typename Enc, typename UnaryFunc>
void forEachCodePoint(EncodedRange<It, Enc> str, UnaryFunc func)
{
    auto it = makeForwardIterator(str);
    uint32_t c;
    while (it.next(c))
        func(c);
}

template <typename It, typename Enc, typename UnaryFunc>
EncodedRange<It, Enc> forEachLine(
        EncodedRange<It, Enc> str, UnaryFunc tokenFunc,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return makeEncodedRange(forEachLine(
            makeForwardIterator(str), tokenFunc, maxParts, flags));
}

template <typename It, typename Enc, typename UnaryFunc>
void forEachLower(EncodedRange<It, Enc> str, UnaryFunc func)
{
    forEachCodePoint(str, [&](uint32_t c){func(Unicode::lower(c));});
}

template <typename It, typename Enc, typename UnaryFunc>
void forEachTitle(EncodedRange<It, Enc> str, UnaryFunc func)
{
    bool capNext = true;
    auto it = makeForwardIterator(str);
    uint32_t c;
    while (it.next(c))
    {
        if (!Unicode::isCasedLetter(c))
        {
            func(c);
            capNext = !Unicode::isLetter(c);
        }
        else if (capNext)
        {
            func(Unicode::title(c));
            capNext = false;
        }
        else
        {
            func(Unicode::lower(c));
        }
    }
}

template <typename It, typename Enc, typename UnaryPred,
          typename UnaryFunc>
EncodedRange<It, Enc> forEachToken(
        EncodedRange<It, Enc> str, UnaryPred delimiterPred,
        UnaryFunc tokenFunc,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return makeEncodedRange(forEachToken(
            makeForwardIterator(str), delimiterPred,
            tokenFunc, maxParts, flags));
}

template <typename It1, typename Enc1, typename It2, typename Enc2,
          typename UnaryFunc>
EncodedRange<It1, Enc1> forEachToken(
        EncodedRange<It1, Enc1> str, EncodedRange<It2, Enc2> delimiter,
        UnaryFunc tokenFunc,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    return makeEncodedRange(forEachToken(
            makeForwardIterator(str), makeForwardIterator(delimiter),
            tokenFunc, maxParts, flags));
}

template <typename It, typename Enc, typename UnaryFunc>
void forEachUpper(EncodedRange<It, Enc> str, UnaryFunc func)
{
    forEachCodePoint(str, [&](uint32_t c){func(Unicode::upper(c));});
}

template <typename It, typename Enc>
bool isAlphaNumeric(EncodedRange<It, Enc> str)
{
    auto it = makeForwardIterator(str);
    return !empty(str) && advanceWhile(it, Unicode::isAlphaNumeric);
}

template <typename It, typename Enc>
EncodedRange<It, Enc> nextLine(EncodedRange<It, Enc>& str)
{
    auto it = makeForwardIterator(str);
    auto line = makeEncodedRange(nextLine(it));
    it.setBegin(begin(it));
    return line;
}

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> nextToken(EncodedRange<It, Enc>& str, UnaryPred pred)
{
    auto it = makeForwardIterator(str);
    auto token = makeEncodedRange(nextToken(it, pred));
    str.setBegin(end(it));
    return token;
}

template <typename It, typename Enc>
It nthCharacter(EncodedRange<It, Enc> str, ptrdiff_t n)
{
    if (n >= 0)
    {
        auto it = makeForwardIterator(str);
        advanceCharacters(it, n);
        return begin(it);
    }
    else
    {
        auto it = makeReverseIterator(str);
        advanceCharacters(it, -n);
        return end(it);
    }
}

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> prevToken(EncodedRange<It, Enc>& str, UnaryPred pred)
{
    auto it = makeReverseIterator(str);
    auto token = makeEncodedRange(nextToken(it, pred));
    str.setEnd(end(it));
    return token;
}

template <typename String, typename It1, typename Enc1,
          typename It2, typename Enc2, typename It3, typename Enc3>
String& replace(String& dst,
                EncodedRange<It1, Enc1> str,
                EncodedRange<It2, Enc2> cmp,
                EncodedRange<It3, Enc3> subst,
                size_t max /*= 0*/,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    auto first = begin(str);
    auto match = findNext(str, cmp, flags);
    while (!empty(match))
    {
        dst.insert(end(dst), first, begin(match));
        dst.insert(end(dst), begin(subst), end(subst));
        first = begin(str);
        if (--max == 0)
            break;
        match = findNext(str, cmp, flags);
    }
    dst.insert(end(dst), first, end(str));
    return dst;
}

template <typename InpIt, typename Enc1, typename OutIt, typename Enc2>
void reverse(EncodedRange<InpIt, Enc1> src, Encoder<OutIt, Enc2> dst)
{
    auto it = makeReverseIterator(src);
    while (advanceCharacter(it))
    {
        src.setBegin(end(it));
        copy(src, dst);
        src.setEnd(src.begin());
    }
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool startsWith(EncodedRange<It1, Enc1> str, EncodedRange<It2, Enc2> cmp,
                FindFlags_t flags /*= FindFlags::Defaults*/)
{
    return startsWith(makeForwardIterator(str),
                      makeForwardIterator(cmp),
                      flags);
}

template <typename It, typename Enc>
size_t stringLength(EncodedRange<It, Enc> str)
{
    auto it = makeForwardIterator(str);
    return advanceCharacters(it, std::numeric_limits<ptrdiff_t>::max());
}

template <typename It, typename Enc>
EncodedRange<It, Enc> substring(
        EncodedRange<It, Enc> str,
        ptrdiff_t first,
        ptrdiff_t last /*= std::numeric_limits<long>::max()*/)
{
    if (0 <= first)
    {
        str.setBegin(nthCharacter(str, first));
        if (last < 0)
            str.setEnd(nthCharacter(str, last));
        else if (first <= last)
            str.setEnd(nthCharacter(str, last - first));
        else
            str.setEnd(str.begin());
    }
    else if (0 <= last)
    {
        auto newBegin = nthCharacter(str, first);
        if (std::distance(begin(str), newBegin) <= last)
            str.setEnd(nthCharacter(str, last));
        else
            str.setEnd(newBegin);
        str.setBegin(newBegin);
    }
    else
    {
        str.setEnd(nthCharacter(str, last));
        if (first < last)
            str.setBegin(nthCharacter(str, first - last));
        else
            str.setBegin(str.end());
    }
    return str;
}

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trim(EncodedRange<It, Enc> str, UnaryPred trimChar)
{
    return trimBack(trimFront(str, trimChar), trimChar);
}


template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trimFront(EncodedRange<It, Enc> str,
                                UnaryPred trimChar)
{
    auto first = makeForwardIterator(str);
    advanceWhile(first, trimChar);
    return makeEncodedRange(first);
}

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trimBack(EncodedRange<It, Enc> str,
                               UnaryPred trimChar)
{
    auto last = makeReverseIterator(str);
    advanceWhile(last, trimChar);
    return makeEncodedRange(last);
}

}}
