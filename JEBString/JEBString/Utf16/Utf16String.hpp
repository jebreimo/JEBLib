#ifndef JEBSTRING_UTF16_UTF16STRING_HPP
#define JEBSTRING_UTF16_UTF16STRING_HPP

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "JEBString/JEBStringFlags.hpp"

/** @file
  * @brief Defines functions for working with UTF-16 encoded std::wstring
  */

/** @brief The namespace for functions working with UTF-16 encoded std::wstring
  *
  * @note It is not safe to use any function that involve case conversion in
  *     the initialization of static variables. The case-conversion code itself
  *     relies on static variables being initialized, and the initialization
  *     order of static variables is unpredictable.
  */
namespace JEBString { namespace Utf16 {

typedef std::pair<std::wstring::const_iterator, std::wstring::const_iterator>
    StringRange;

typedef std::pair<std::wstring::iterator, std::wstring::iterator>
    MutableStringRange;

/** @brief Adds @a codePoint encoded as UTF-16 to the end of@a str.
  */
std::wstring& append(std::wstring& str, uint32_t chr);

/** @brief Iterates over the values between @a first and @a last and appends
  *     them to @a dst.
  *
  * The values in the range must be convertible to std::wstring.
  * The dereferenced value at @a first will be appended as the first value,
  * last will not be dereferenced.
  */
template <typename FwdIt>
std::wstring& appendJoin(std::wstring& dst, FwdIt first, FwdIt last);

/** @brief Iterates over the values between @a first and @a last and appends
  *     them to @a dst delimited by separator.
  *
  * The values in the range must be convertible to std::wstring.
  * The dereferenced value at @a first will be appended as the first value,
  * last will not be dereferenced.
  */
template <typename FwdIt>
std::wstring& appendJoin(std::wstring& dst, FwdIt first, FwdIt last,
                        const std::wstring& separator);

/** @brief Compares @a str and @a cmp, ignoring any differences in
  *     letter casing.
  *  @returns @arg < 0 if @a str is less than @a cmp
  *           @arg 0 if @a str is equal to @a cmp
  *           @arg > 0 if @a str is greater than @a cmp
  */
int32_t caseInsensitiveCompare(const std::wstring& str,
                               const std::wstring& cmp);

/** @brief Returns true if the upper case versions of @a str and @a cmp
  *     are equal.
  */
bool caseInsensitiveEqual(const std::wstring& str, const std::wstring& cmp);

/** @brief Returns true if the upper case version of @a str is less than
  *     @a cmp.
  *
  * Only a quick comparison of code point values are performed. This
  * function should not be used to sort strings in alphabetical order as
  * what is alphabetical order varies betweem languages and cultures.
  */
bool caseInsensitiveLess(const std::wstring& str, const std::wstring& cmp);

/** @brief Returns true if @a str contains character (code point) @a chr.
  */
bool contains(const std::wstring& str, uint32_t chr);

/** @brief Returns true if @a str ends with @a cmp.
  */
bool endsWith(const std::wstring& str,
              const std::wstring& cmp,
              FindFlags_t flags = FindFlags::Defaults);

StringRange findSubstring(const std::wstring& str,
                          const std::wstring& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(std::wstring& str,
                                 const std::wstring& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

StringRange findSubstring(StringRange str,
                          const std::wstring& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(MutableStringRange str,
                                 const std::wstring& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

std::wstring insert(const std::wstring& str, ptrdiff_t pos,
                   const std::wstring& sub);

std::wstring insert(const std::wstring& str, ptrdiff_t pos, uint32_t chr);

std::wstring& insertInPlace(std::wstring& str, ptrdiff_t pos,
                           const std::wstring& sub);

template <typename FwdIt>
bool isAlphaNumeric(FwdIt first, FwdIt last);

bool isAlphaNumeric(const std::wstring& str);

/** @brief Returns true if all characters in @a str are valid UTF-16.
  */
bool isValidUtf16(const std::wstring& str);

/** @brief Returns a single string that is the concatenation of the strings
  *     from @a first to @a last.
  *
  * @param first    the first string in the result.
  * @param last     the end of the range starting at @a first.
  * @param parts    the strings that will be joined
  */
template <typename FwdIt>
std::wstring join(FwdIt first, FwdIt last);

/** @brief Returns a single string that is the concatenation of the strings
  *     from @a first to @a last.
  *
  * @param first    the first string in the result.
  * @param last     the end of the range starting at @a first.
  * @param separator the strings in @a parts will be separated by this.
  */
template <typename FwdIt>
std::wstring join(FwdIt first, FwdIt last, const std::wstring& separator);

/** @brief Returns a copy of @a str with all letters lower-cased.
  */
std::wstring lower(const std::wstring& str);

std::wstring::iterator nthCharacter(std::wstring& str, ptrdiff_t n);
std::wstring::const_iterator nthCharacter(const std::wstring& str, ptrdiff_t n);

/** @brief Returns a copy of @a str where instances of @a from are replaced
  *      with @a to.
  *
  * @param max The maximum number of replacements that will be performed. All
  *      instances of @a from are replaced if 0.
  */
std::wstring replace(const std::wstring& str,
                    const std::wstring& from,
                    const std::wstring& to,
                    size_t max = 0,
                    FindFlags_t flags = FindFlags::Defaults);

/** @brief Returns a copy of @a str with instances of @a fromChar replaced
  *      with @a toChar.
  *
  *  @param fromChar The character to replace
  *  @param toChar The replacement
  *  @param max The maximum number of replacements that will be performed. All
  *      instances of @a from are replaced if 0.
  */
std::wstring replaceCodePoint(const std::wstring& s,
                             uint32_t fromChar,
                             uint32_t toChar,
                             size_t max = 0);

std::wstring replace(const std::wstring& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::wstring& repl);

std::wstring& replaceInPlace(std::wstring& str,
                            ptrdiff_t start,
                            ptrdiff_t end,
                            const std::wstring& repl);

std::wstring replaceInvalidUtf16(const std::wstring& str, uint32_t chr = '?');

std::wstring& replaceInvalidUtf16InPlace(std::wstring& str, char chr = '?');

/** @brief Returns a reversed copy of @a str.
  *
  * Characters with combining marks are left intact.
  */
std::wstring reverse(const std::wstring& str);

std::vector<std::wstring> split(
        const std::wstring& str,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::IgnoreEmpty);

std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& sep,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

template <typename UnaryPred>
std::vector<std::wstring> splitIf(
        const std::wstring& str,
        UnaryPred delimiterPredicate,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

std::vector<std::wstring> splitLines(
        const std::wstring& str,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

bool startsWith(const std::wstring& str,
                const std::wstring& cmp,
                FindFlags_t flags = FindFlags::Defaults);

/** @brief Returns the number of code points from @a begin to @a end.
  *
  * @return the number of code points.
  * @throw runtime_error if str contains an invalid UTF-16 code point.
  */
size_t stringLength(const std::wstring& str);

template <typename FwdIt>
size_t stringLength(FwdIt first, FwdIt last);

std::wstring substring(
        const std::wstring& str,
        ptrdiff_t startIndex,
        ptrdiff_t endIndex = std::numeric_limits<ptrdiff_t>::max());

std::wstring substring(const std::wstring& str,
                      std::pair<size_t, size_t>& indexes);

/** @brief Returns a copy of @a str with all words capitalized.
  */
std::wstring title(const std::wstring& str);

/** @brief Returns a UTF-16 encoded string representing @a chr
  */
std::wstring toString(uint32_t chr);

/** @brief Returns the UTF-16 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
std::wstring toUtf16(const std::string& str, Encoding_t encoding);

/** @brief Returns the UTF-16 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't a 16-bit encoding.
  */
std::wstring toUtf16(const std::wstring& str,
                   Encoding_t encoding = Encoding::Utf16);

std::wstring trim(const std::wstring& str);

template <typename UnaryPred>
std::wstring trim(const std::wstring& str, UnaryPred predicate);

std::wstring trimFront(const std::wstring& str);

template <typename UnaryPred>
std::wstring trimFront(const std::wstring& str, UnaryPred predicate);

std::wstring trimBack(const std::wstring& str);

template <typename UnaryPred>
std::wstring trimBack(const std::wstring& str, UnaryPred predicate);

std::wstring upper(const std::wstring& str);

}}

#include "Utf16String_impl.hpp"

#endif
