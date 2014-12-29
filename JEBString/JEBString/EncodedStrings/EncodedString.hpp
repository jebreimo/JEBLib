#ifndef JEBSTRING_ENCODEDSTRINGS_ENCODEDSTRING_HPP
#define JEBSTRING_ENCODEDSTRINGS_ENCODEDSTRING_HPP

#include <limits>
#include "Encoder.hpp"
#include "EncodedRange.hpp"

namespace JEBString { namespace EncodedStrings {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::Encoder;

template <typename It1, typename Enc1, typename It2, typename Enc2>
int32_t caseInsensitiveCompare(EncodedRange<It1, Enc1> str,
                               EncodedRange<It2, Enc2> cmp);

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool caseInsensitiveEqual(EncodedRange<It1, Enc1> str,
                          EncodedRange<It2, Enc2> cmp);

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool caseInsensitiveLess(EncodedRange<It1, Enc1> str,
                         EncodedRange<It2, Enc2> cmp);

template <typename It, typename Enc>
bool contains(EncodedRange<It, Enc> str, uint32_t chr);

template <typename InpIt, typename Enc1, typename OutIt, typename Enc2>
void copy(EncodedRange<InpIt, Enc1> src, Encoder<OutIt, Enc2> dst);

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool endsWith(EncodedRange<It1, Enc1> str, EncodedRange<It2, Enc2> cmp,
              FindFlags_t flags = FindFlags::Defaults);

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> find(EncodedRange<It1, Enc1> str,
                             EncodedRange<It2, Enc2> cmp,
                             FindFlags_t flags = FindFlags::Defaults);

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> findNext(EncodedRange<It1, Enc1>& str,
                                 EncodedRange<It2, Enc2> cmp,
                                 FindFlags_t flags = FindFlags::Defaults);

template <typename It, typename Enc, typename UnaryFunc>
EncodedRange<It, Enc> forEachLine(
        EncodedRange<It, Enc> str, UnaryFunc tokenFunc,
        size_t maxParts = 0, SplitFlags_t flags = SplitFlags::Defaults);

template <typename It, typename Enc, typename UnaryFunc>
void forEachLower(EncodedRange<It, Enc> str, UnaryFunc func);

template <typename It, typename Enc, typename UnaryFunc>
void forEachTitle(EncodedRange<It, Enc> str, UnaryFunc func);

template <typename It, typename Enc, typename UnaryPred,
          typename UnaryFunc>
EncodedRange<It, Enc> forEachToken(
        EncodedRange<It, Enc> str, UnaryPred delimiterPred,
        UnaryFunc tokenFunc,
        size_t maxParts = 0, SplitFlags_t flags = SplitFlags::Defaults);

template <typename It1, typename Enc1, typename It2, typename Enc2,
          typename UnaryFunc>
EncodedRange<It1, Enc1> forEachToken(
        EncodedRange<It1, Enc1> str, EncodedRange<It2, Enc2> delimiter,
        UnaryFunc tokenFunc,
        size_t maxParts = 0, SplitFlags_t flags = SplitFlags::Defaults);

template <typename It, typename Enc, typename UnaryFunc>
void forEachUpper(EncodedRange<It, Enc> str, UnaryFunc func);

template <typename It, typename Enc>
bool isAlphaNumeric(EncodedRange<It, Enc> str);

template <typename It, typename Enc>
EncodedRange<It, Enc> nextLine(EncodedRange<It, Enc>& str);

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> nextToken(EncodedRange<It, Enc>& str, UnaryPred func);

template <typename It, typename Enc>
It nthCharacter(EncodedRange<It, Enc> str, ptrdiff_t n);

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> prevToken(EncodedRange<It, Enc>& str, UnaryPred func);

template <typename String, typename It1, typename Enc1,
          typename It2, typename Enc2, typename It3, typename Enc3>
String& replace(String& dst,
                EncodedRange<It1, Enc1> str,
                EncodedRange<It2, Enc2> cmp,
                EncodedRange<It3, Enc3> subst,
                size_t max = 0,
                FindFlags_t flags = FindFlags::Defaults);

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool startsWith(EncodedRange<It1, Enc1> str,
                EncodedRange<It2, Enc2> cmp,
                FindFlags_t flags = FindFlags::Defaults);

/** @brief Returns the number of complete characters in @a str.
  *
  *  Only complete characters are counted, combining marks are ignored.
  */
template <typename It, typename Enc>
size_t stringLength(EncodedRange<It, Enc> str);

template <typename It, typename Enc>
EncodedRange<It, Enc> substring(
        EncodedRange<It, Enc> str,
        ptrdiff_t first,
        ptrdiff_t last = std::numeric_limits<long>::max());

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trim(EncodedRange<It, Enc> str, UnaryPred trimChar);

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trimFront(EncodedRange<It, Enc> str,
                                UnaryPred trimChar);

template <typename It, typename Enc, typename UnaryPred>
EncodedRange<It, Enc> trimBack(EncodedRange<It, Enc> str,
                               UnaryPred trimChar);

}}

#include "EncodedString_impl.hpp"

#endif
