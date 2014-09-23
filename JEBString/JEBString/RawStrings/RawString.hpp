#ifndef JEBSTRING_RAWSTRINGS_RAWSTRING_HPP
#define JEBSTRING_RAWSTRINGS_RAWSTRING_HPP

#include <string>
#include "JEBBase/Ranges/Range.hpp"
#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace RawStrings {

using JEBBase::Ranges::Range;

/** @brief Adds to @a dst the concatenation of the strings
  *         in @a first ... @a last separated by @a sep.
  */
template <typename String, typename ContainerIt, typename DelimiterString>
String& appendJoin(String& str, ContainerIt first, ContainerIt last,
                   const DelimiterString& delimiter);

/** @brief Adds to @a str the concatenation of the strings
  *         in @a first ... @a last.
  */
template <typename String, typename ContainerIt>
String& appendJoin(String& str, ContainerIt first, ContainerIt last);

template <typename It, typename UnaryPred, typename UnaryFunc>
Range<It> forEachToken(Range<It> str, UnaryPred delimiter,
                       UnaryFunc tokenFunc, size_t maxParts = 0,
                       SplitFlags_t flags = SplitFlags::Defaults);

template <typename String, typename ContainerIt, typename DelimiterString>
String join(ContainerIt first, ContainerIt last,
            const DelimiterString& delimiter);

template <typename String, typename ContainerIt>
String join(ContainerIt first, ContainerIt last);

template <typename It, typename UnaryPred>
Range<It> nextToken(Range<It>& str, UnaryPred delimiter);

template <typename It, typename UnaryPred>
Range<It> prevToken(Range<It>& str, UnaryPred delimiter);

template <typename It, typename UnaryPred>
std::vector<Range<It>> splitIf(Range<It> str, UnaryPred delimiter,
                               size_t maxParts = 0,
                               SplitFlags_t flags = SplitFlags::Defaults);

template <typename CharType, typename It>
std::basic_string<CharType> toString(Range<It> range);

}}

#include "RawString.impl.hpp"

#endif
