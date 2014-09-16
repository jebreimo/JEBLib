#include "JEBString/CodePageStrings/CodePageString.hpp"
#include "JEBString/Utf8/Utf8Chars.hpp"

#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace JEBString;
using namespace JEBString::CodePageStrings;

void test_caseInsensitiveCompare()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_EQUAL(caseInsensitiveCompare(cp, "Ab123\xC0\xE6", "aB123\xE0\xE6"), 0);
    JT_GREATER(caseInsensitiveCompare(cp,
                                      "Ab123\xC1\xE6", "aB123\xE0\xE6"), 0);
    JT_LESS(caseInsensitiveCompare(cp, "aB123\xE0\xE6", "Ab123\xC1\xE6"), 0);
}

void test_caseInsensitiveEqual()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_ASSERT(caseInsensitiveEqual(cp, "Ab123\xC0\xE6", "aB123\xE0\xE6"));
    JT_ASSERT(!caseInsensitiveEqual(cp, "Ab123\xC1\xE6", "aB123\xE0\xE6"));
}

void test_caseInsensitiveLess()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_ASSERT(!caseInsensitiveLess(cp, "Ab123\xC0\xE6", "aB123\xE0\xE6"));
    JT_ASSERT(!caseInsensitiveLess(cp, "aB123\xE0\xE6", "Ab123\xC0\xE6"));
    JT_ASSERT(caseInsensitiveLess(cp, "Ab123\xE0\xE6", "aB123\xC1\xE6"));
}

void test_endsWith()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_ASSERT(endsWith(cp, "abcdefghi\xC0", "Hi\xE0",
                       JEBString::FindFlags::CaseInsensitive));
    JT_ASSERT(!endsWith(cp, "abcdefghi\xC0", "Hi\xE0"));
}

void test_findSubstring_const()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    auto range = findSubstring(cp, "abc\xE6Qhjk", "C\xC6q",
                               JEBString::FindFlags::CaseInsensitive);
    JT_EQUAL(std::string(range.first, range.second), "c\xE6Q");
}

void test_findSubstring_nonconst()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    std::string s("abc\xE6Qhjk");
    auto range = findSubstring(cp, s, "C\xC6q",
                               JEBString::FindFlags::CaseInsensitive);
    JT_EQUAL(std::string(range.first, range.second), "c\xE6Q");
}

void test_lower()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    auto str = "aB\xC0\xE6+8";
    JT_EQUAL(lower(cp, str), "ab\xE0\xE6+8");
}

void test_replace()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_EQUAL(replace(cp, "foo_aR\xC0_bar_ar\xE0_baz", "AR\xC0", "bom"),
             "foo_aR\xC0_bar_ar\xE0_baz");
    JT_EQUAL(replace(cp, "foo_aR\xC0_bar_ar\xE0_baz", "AR\xC0", "bom", 0,
                     JEBString::FindFlags::CaseInsensitive),
             "foo_bom_bar_bom_baz");
    JT_EQUAL(replace(cp, "foo_aR\xC0_bar_ar\xE0_baz", "AR\xC0", "bom", 1,
                     JEBString::FindFlags::CaseInsensitive),
             "foo_bom_bar_ar\xE0_baz");
    JT_EQUAL(replace(cp, "foo_aR\xC0_bar_ar\xE0_baz", "AR\xC0", "bom", 2,
                     JEBString::FindFlags::CaseInsensitive),
             "foo_bom_bar_bom_baz");
}

void test_split()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    auto parts = split(cp, "123k\xC4mK\xE4M456K\xE4m789k\xC4M", "k\xC4m",
                       0, JEBString::SplitFlags::CaseInsensitive);
    JT_EQUAL(parts.size(), 5);
    JT_EQUAL(parts[0], "123");
    JT_EQUAL(parts[1], "");
    JT_EQUAL(parts[2], "456");
    JT_EQUAL(parts[3], "789");
    JT_EQUAL(parts[4], "");
    auto parts2 = split(cp, "123k\xC4mK\xE4M456K\xE4m789k\xC4M", "k\xC4m", 0,
                        JEBString::SplitFlags::CaseInsensitive |
                        JEBString::SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts2.size(), 3);
    JT_EQUAL(parts2[0], "123");
    JT_EQUAL(parts2[1], "456");
    JT_EQUAL(parts2[2], "789");
}

void test_startsWith()
{
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_ASSERT(startsWith(cp, "aB\xC0-cdefghi", "Ab\xE0-",
                         JEBString::FindFlags::CaseInsensitive));
    JT_ASSERT(!startsWith(cp, "aB\xC0-cdefghi", "Ab\xE0-"));
}

void test_title()
{
    auto str = "aB\xC0\xE6+8 foO";
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_EQUAL(title(cp, str), "Ab\xE0\xE6+8 Foo");
}

void test_toCodePageString_fromUtf8()
{
    auto str = UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
               UTF8_LATIN_SMALL_O_WITH_STROKE "ker";
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_EQUAL(toCodePageString(cp, str, Encoding::Utf8), "\xC5rb\xF8ker");
}

void test_upper()
{
    auto str = "aB\xC0\xE6+8";
    auto cp = codePage(JEBString::Encoding::Windows1252);
    JT_EQUAL(upper(cp, str), "AB\xC0\xC6+8");
}

JT_SUBTEST("CodePages",
           test_caseInsensitiveCompare,
           test_caseInsensitiveEqual,
           test_caseInsensitiveLess,
           test_endsWith,
           test_findSubstring_const,
           test_findSubstring_nonconst,
           test_lower,
           test_replace,
           test_split,
           test_startsWith,
           test_title,
           test_toCodePageString_fromUtf8,
           test_upper);
}
