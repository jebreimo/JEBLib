#ifndef JEBSTRING_UTF8_UTF8STRING_HPP
#define JEBSTRING_UTF8_UTF8STRING_HPP

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "JEBString/JEBStringFlags.hpp"

/** @file
  * @brief Defines functions for working with UTF-8 encoded std::string
  */

/** @brief The namespace for functions working with UTF-8 encoded std::string
  *
  * @note It is not safe to use any function that involve case conversion in
  *     the initialization of static variables. The case-conversion code itself
  *     relies on static variables being initialized, and the initialization
  *     order of static variables is unpredictable.
  */
namespace JEBString { namespace Utf8 {

typedef std::pair<std::string::const_iterator, std::string::const_iterator>
    StringRange;

typedef std::pair<std::string::iterator, std::string::iterator>
    MutableStringRange;

/** @brief Adds @a codePoint encoded as UTF-8 to the end of@a str.
  */
std::string& append(std::string& str, uint32_t chr);

/** @brief Iterates over the values between @a first and @a last and appends
  *     them to @a dst.
  *
  * The values in the range must be convertible to std::string.
  * The dereferenced value at @a first will be appended as the first value,
  * last will not be dereferenced.
  */
template <typename FwdIt>
std::string& appendJoin(std::string& dst, FwdIt first, FwdIt last);

/** @brief Iterates over the values between @a first and @a last and appends
  *     them to @a dst delimited by separator.
  *
  * The values in the range must be convertible to std::string.
  * The dereferenced value at @a first will be appended as the first value,
  * last will not be dereferenced.
  */
template <typename FwdIt>
std::string& appendJoin(std::string& dst, FwdIt first, FwdIt last,
                        const std::string& separator);

/** @brief Compares @a str and @a cmp, ignoring any differences in
  *     letter casing.
  *  @returns @arg < 0 if @a str is less than @a cmp
  *           @arg 0 if @a str is equal to @a cmp
  *           @arg > 0 if @a str is greater than @a cmp
  */
int32_t caseInsensitiveCompare(const std::string& str,
                               const std::string& cmp);

/** @brief Returns true if the upper case versions of @a str and @a cmp
  *     are equal.
  */
bool caseInsensitiveEqual(const std::string& str, const std::string& cmp);

/** @brief Returns true if the upper case version of @a str is less than
  *     @a cmp.
  *
  * Only a quick comparison of code point values are performed. This
  * function should not be used to sort strings in alphabetical order as
  * what is alphabetical order varies betweem languages and cultures.
  */
bool caseInsensitiveLess(const std::string& str, const std::string& cmp);

/** @brief Returns true if @a str contains character (code point) @a chr.
  */
bool contains(const std::string& str, uint32_t chr);

/** @brief Returns true if @a str ends with @a cmp.
  */
bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags = FindFlags::Defaults);

std::string escape(const std::string& str);

StringRange findSubstring(const std::string& str,
                          const std::string& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(std::string& str,
                                 const std::string& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

StringRange findSubstring(StringRange str,
                          const std::string& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(MutableStringRange str,
                                 const std::string& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

std::string insert(const std::string& str, ptrdiff_t pos,
                   const std::string& sub);

std::string insert(const std::string& str, ptrdiff_t pos, uint32_t chr);

std::string& insertInPlace(std::string& str, ptrdiff_t pos,
                           const std::string& sub);

template <typename FwdIt>
bool isAlphaNumeric(FwdIt first, FwdIt last);

bool isAlphaNumeric(const std::string& str);

/** @brief Returns true if all characters in @a str are valid UTF-8.
  */
bool isValidUtf8(const std::string& str);

/** @brief Returns a single string that is the concatenation of the strings
  *     from @a first to @a last.
  *
  * @param first    the first string in the result.
  * @param last     the end of the range starting at @a first.
  * @param parts    the strings that will be joined
  */
template <typename FwdIt>
std::string join(FwdIt first, FwdIt last);

/** @brief Returns a single string that is the concatenation of the strings
  *     from @a first to @a last.
  *
  * @param first    the first string in the result.
  * @param last     the end of the range starting at @a first.
  * @param separator the strings in @a parts will be separated by this.
  */
template <typename FwdIt>
std::string join(FwdIt first, FwdIt last, const std::string& separator);

/** @brief Returns a copy of @a str with all letters lower-cased.
  */
std::string lower(const std::string& str);

std::string::iterator nthCharacter(std::string& str, ptrdiff_t n);
std::string::const_iterator nthCharacter(const std::string& str, ptrdiff_t n);

/** @brief Returns a copy of @a str where instances of @a from are replaced
  *      with @a to.
  *
  * @param max The maximum number of replacements that will be performed. All
  *      instances of @a from are replaced if 0.
  */
std::string replace(const std::string& str,
                    const std::string& from,
                    const std::string& to,
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
std::string replaceCodePoint(const std::string& s,
                             uint32_t fromChar,
                             uint32_t toChar,
                             size_t max = 0);

std::string replace(const std::string& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::string& repl);

std::string& replaceInPlace(std::string& str,
                            ptrdiff_t start,
                            ptrdiff_t end,
                            const std::string& repl);

std::string replaceInvalidUtf8(const std::string& str, uint32_t chr = '?');

std::string& replaceInvalidUtf8InPlace(std::string& str, char chr = '?');

/** @brief Returns a reversed copy of @a str.
  *
  * Characters with combining marks are left intact.
  */
std::string reverse(const std::string& str);

std::vector<std::string> split(
        const std::string& str,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::IgnoreEmpty);

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

template <typename UnaryPred>
std::vector<std::string> splitIf(
        const std::string& str,
        UnaryPred delimiterPredicate,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

std::vector<std::string> splitLines(
        const std::string& str,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags = FindFlags::Defaults);

/** @brief Returns the number of code points from @a begin to @a end.
  *
  * @return the number of code points.
  * @throw runtime_error if str contains an invalid UTF-8 code point.
  */
size_t stringLength(const std::string& str);

template <typename FwdIt>
size_t stringLength(FwdIt first, FwdIt last);

std::string substring(
        const std::string& str,
        ptrdiff_t startIndex,
        ptrdiff_t endIndex = std::numeric_limits<ptrdiff_t>::max());

std::string substring(const std::string& str,
                      std::pair<size_t, size_t>& indexes);

/** @brief Returns a copy of @a str with all words capitalized.
  */
std::string title(const std::string& str);

/** @brief Returns a UTF-8 encoded string representing @a chr
  */
std::string toString(uint32_t chr);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
std::string toUtf8(const std::string& str, Encoding_t encoding);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't a 16-bit encoding.
  */
std::string toUtf8(const std::wstring& str,
                   Encoding_t encoding = Encoding::Utf16);

std::string trim(const std::string& str);

template <typename UnaryPred>
std::string trim(const std::string& str, UnaryPred predicate);

std::string trimFront(const std::string& str);

template <typename UnaryPred>
std::string trimFront(const std::string& str, UnaryPred predicate);

std::string trimBack(const std::string& str);

template <typename UnaryPred>
std::string trimBack(const std::string& str, UnaryPred predicate);

std::string unescape(const std::string& str);

std::string upper(const std::string& str);

}}

#include "Utf8String_impl.hpp"

#endif
