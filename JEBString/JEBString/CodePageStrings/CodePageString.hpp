#ifndef JEBSTRING_CODEPAGES_CODEPAGESTRING_HPP
#define JEBSTRING_CODEPAGES_CODEPAGESTRING_HPP

#include <string>
#include <vector>
#include "JEBString/JEBStringFlags.hpp"
#include "CodePage.hpp"

namespace JEBString { namespace CodePageStrings {

typedef std::pair<std::string::const_iterator, std::string::const_iterator>
    StringRange;

typedef std::pair<std::string::iterator, std::string::iterator>
    MutableStringRange;

int32_t caseInsensitiveCompare(const CodePage& codePage,
                               const std::string& str,
                               const std::string& cmp);

bool caseInsensitiveEqual(const CodePage& codePage,
                          const std::string& str,
                          const std::string& cmp);

bool caseInsensitiveLess(const CodePage& codePage,
                         const std::string& str,
                         const std::string& cmp);

bool endsWith(const CodePage& codePage,
              const std::string& str,
              const std::string& cmp,
              FindFlags_t flags = FindFlags::Defaults);

StringRange findSubstring(const CodePage& codePage,
                          const std::string& str,
                          const std::string& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(const CodePage& codePage,
                                 std::string& str,
                                 const std::string& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

StringRange findSubstring(const CodePage& codePage,
                          StringRange str,
                          const std::string& sub,
                          FindFlags_t flags = FindFlags::Defaults);

MutableStringRange findSubstring(const CodePage& codePage,
                                 MutableStringRange str,
                                 const std::string& sub,
                                 FindFlags_t flags = FindFlags::Defaults);

std::string lower(const CodePage& codePage, const std::string& str);

StringRange nextToken(const CodePage& codePage,
                      StringRange& str,
                      const std::string& delimiter,
                      FindFlags_t flags = FindFlags::Defaults);

std::string replace(const CodePage& codePage,
                    const std::string& str,
                    const std::string& from,
                    const std::string& to,
                    size_t max = 0,
                    FindFlags_t flags = FindFlags::Defaults);


std::vector<std::string> split(
        const CodePage& codePage,
        const std::string& str,
        const std::string& sep,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::Defaults);

bool startsWith(const CodePage& codePage,
                const std::string& str,
                const std::string& cmp,
                FindFlags_t flags = FindFlags::Defaults);

std::string title(const CodePage& codePage, const std::string& str);
std::string& toLower(const CodePage& codePage, std::string& str);
std::string& toTitle(const CodePage& codePage, std::string& str);
std::string& toUpper(const CodePage& codePage, std::string& str);

std::string toCodePageString(const CodePage& codePage, const std::string str,
                             Encoding_t encoding,
                             char unsupportedCodePointPlaceHolder = '?');
std::string toCodePageString(const CodePage& codePage, const std::wstring str,
                             Encoding_t encoding,
                             char unsupportedCodePointPlaceHolder = '?');

std::string upper(const CodePage& codePage, const std::string& str);

}}

#endif
