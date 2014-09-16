#ifndef JEBSTRING_CODEPOINTS_CODEPOINTALGORITHMS_HPP
#define JEBSTRING_CODEPOINTS_CODEPOINTALGORITHMS_HPP

#include <cstdint>
#include <algorithm>
#include "CodePointIterator.hpp"

namespace JEBString { namespace CodePoints {

struct AdvanceResult
{
    enum Type
    {
        Success,
        Failure,
        EndOfString
    };
};

typedef AdvanceResult::Type AdvanceResult_t;

template <typename Decoder, typename UnaryPred>
bool advanceIf(CodePointIterator<Decoder>& it, UnaryPred pred)
{
    auto posIt = it.internalBegin();
    uint32_t ch;
    if (!it.next(ch) || !pred(ch))
    {
        it.setInternalBegin(posIt);
        return false;
    }
    return true;
}

template <typename Decoder, typename UnaryPred>
bool advanceUntil(CodePointIterator<Decoder>& it, UnaryPred pred)
{
    while (advanceIf(it, [&](uint32_t ch){return !pred(ch);}))
    {}
    return !empty(it);
}

template <typename Decoder, typename UnaryPred>
bool advanceWhile(CodePointIterator<Decoder>& it, UnaryPred pred)
{
    while (advanceIf(it, pred))
    {}
    return empty(it);
}

template <typename Decoder1, typename Decoder2, typename BinaryPred>
bool advanceIfEqual(CodePointIterator<Decoder1>& a,
                    CodePointIterator<Decoder2>& b, BinaryPred compare)
{
    auto aPos = a.internalBegin();
    auto bPos = b.internalBegin();
    uint32_t aCh, bCh;
    bool aNext = a.next(aCh);
    bool bNext = b.next(bCh);
    if (!aNext && !bNext)
        return false;
    if (!aNext || !bNext || !compare(aCh, bCh))
    {
        a.setInternalBegin(aPos);
        b.setInternalBegin(bPos);
        return false;
    }
    return true;
}

template <typename Decoder1, typename Decoder2>
bool advanceIfEqual(CodePointIterator<Decoder1>& str,
                    CodePointIterator<Decoder2>& cmp)
{
    return advanceIfEqual(str, cmp,
                          [](uint32_t a, uint32_t b){return a == b;});
}

template <typename Decoder1, typename Decoder2, typename BinaryPred>
bool advanceWhileEqual(CodePointIterator<Decoder1>& str,
                       CodePointIterator<Decoder2>& cmp,
                       BinaryPred compare)
{
    while (advanceIfEqual(str, cmp, compare))
    {
    }
    return empty(cmp);
}

template <typename Decoder1, typename Decoder2>
bool advanceWhileEqual(CodePointIterator<Decoder1>& str,
                       CodePointIterator<Decoder2>& cmp)
{
    return advanceWhileEqual(str, cmp,
                             [](uint32_t a, uint32_t b){return a == b;});
}

template <typename Decoder1, typename Decoder2, typename BinaryPred>
CodePointIterator<Decoder1> search(CodePointIterator<Decoder1>& str,
                                   CodePointIterator<Decoder2>& cmp,
                                   BinaryPred compare)
{
    while (true)
    {
        auto copyOfStr = str;
        auto copyOfCmp = cmp;
        if (advanceWhileEqual(copyOfStr, copyOfCmp, compare))
        {
            str.setInternalEnd(copyOfStr.internalBegin());
            std::swap(str, copyOfStr);
            return copyOfStr;
        }
        if (!str.next())
            break;
    }
    return str;
}

template <typename Decoder1, typename Decoder2>
CodePointIterator<Decoder1> search(CodePointIterator<Decoder1>& str,
                                   CodePointIterator<Decoder2> cmp)
{
    return search(str, cmp, [](uint32_t a, uint32_t b){return a == b;});
}

}}

#endif
