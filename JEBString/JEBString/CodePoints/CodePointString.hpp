#ifndef JEBSTRING_CODEPOINTS_GENERICSTRING_HPP
#define JEBSTRING_CODEPOINTS_GENERICSTRING_HPP

#include <cstdint>
#include <limits>
#include "JEBString/EncodedStrings/Encoder.hpp"
#include "CodePointIterator.hpp"

namespace JEBString { namespace CodePoints {

template <typename Decoder>
bool advanceCharacter(CodePointIterator<Decoder>& it);

template <typename Decoder>
size_t advanceCharacters(CodePointIterator<Decoder>& it, size_t n);

/** @brief Compares @a a and @a b, ignoring any differences in letter casing.
  *  @returns @arg < 0 if @a a is less than @a b
  *           @arg 0 if @a a is equal to @a b
  *           @arg > 0 if @a a is greater than @a b
  */
template <typename Decoder1, typename Decoder2>
int32_t caseInsensitiveCompare(CodePointIterator<Decoder1> a,
                               CodePointIterator<Decoder2> b);

/** @brief Returns true if @a a is equal to @a b when letter casing
  *     is ignored.
  */
template <typename Decoder1, typename Decoder2>
bool caseInsensitiveEqual(CodePointIterator<Decoder1> a,
                          CodePointIterator<Decoder2> b);

/** @brief Returns true if the code points in @a a are less than the
  *     corresponding code points in @a b when letter casing is ignored.
  *
  * @note This function ignores locales and should not be used on data
  *     that is displayed to the user. Its intended area of use is in
  *     sets, maps and their likes.
  */
template <typename Decoder1, typename Decoder2>
bool caseInsensitiveLess(CodePointIterator<Decoder1> a,
                         CodePointIterator<Decoder2> b);

template <typename Decoder, typename OutIt, typename Enc>
void copy(CodePointIterator<Decoder> str,
          EncodedStrings::Encoder<OutIt, Enc> encoder);

template <typename Decoder1, typename Decoder2>
CodePointIterator<Decoder1> find(CodePointIterator<Decoder1>& str,
                                 CodePointIterator<Decoder2> sub,
                                 FindFlags_t flags = FindFlags::Defaults);

template <typename Decoder, typename UnaryFunc>
CodePointIterator<Decoder> forEachLine(
        CodePointIterator<Decoder> str,
        UnaryFunc tokenFunc, size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

template <typename Decoder, typename UnaryPred, typename UnaryFunc>
CodePointIterator<Decoder> forEachToken(CodePointIterator<Decoder> str,
                  UnaryPred delimiterPred,
                  UnaryFunc tokenFunc, size_t maxParts = 0,
                  SplitFlags_t flags = SplitFlags::Defaults);

template <typename Decoder1, typename Decoder2, typename UnaryFunc>
CodePointIterator<Decoder1> forEachStringDelimtedToken(
        CodePointIterator<Decoder1> str,
        CodePointIterator<Decoder2> delimiter, UnaryFunc tokenFunc,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

template <typename Decoder>
CodePointIterator<Decoder> nextLine(CodePointIterator<Decoder>& str);

/** @brief Returns the range of the next newline in @a str.
  *
  * @note A \\r followed by a \\n is considered a single newline character.
  */
template <typename Decoder>
CodePointIterator<Decoder> nextNewline(CodePointIterator<Decoder>& str);

template <typename Decoder, typename UnaryPred>
CodePointIterator<Decoder> nextToken(CodePointIterator<Decoder>& str,
                                     UnaryPred predicate);

template <typename Decoder1, typename Decoder2>
CodePointIterator<Decoder1> nextToken(
        CodePointIterator<Decoder1>& str,
        CodePointIterator<Decoder2> delimiter,
        FindFlags_t flags = FindFlags::Defaults);

template <typename Decoder1, typename Decoder2>
bool startsWith(CodePointIterator<Decoder1> str,
                CodePointIterator<Decoder2> cmp,
                FindFlags_t flags = FindFlags::Defaults);

}}

#include "CodePointString_impl.hpp"

#endif
