#include "../Utf8/Split.hpp"

#include <vector>
#include "../Utf8/Utf8Chars.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEB;

static void test_splitWithoutSepIgnoreEmpty()
{
    std::string test("\n abc def  ghi\t  jkl  ");
    std::vector<std::string> parts;
    String::Utf8::split(parts, test);
    JT_EQUAL(parts.size(), 4);
    JT_EQUAL(parts[0], "abc");
    JT_EQUAL(parts[1], "def");
    JT_EQUAL(parts[2], "ghi");
    JT_EQUAL(parts[3], "jkl");
}

static void test_splitWithoutSep()
{
    std::string test("\n abc def " JEB_UTF8_LINE_SEPARATOR " ghi\t  jkl  ");
    std::vector<std::string> parts;
    String::Utf8::split(parts, test, 0, String::SplitFlags::MergeTokens);
    JT_EQUAL(parts.size(), 6);
    JT_EQUAL(parts[0], "");
    JT_EQUAL(parts[1], "abc");
    JT_EQUAL(parts[2], "def");
    JT_EQUAL(parts[3], "ghi");
    JT_EQUAL(parts[4], "jkl");
    JT_EQUAL(parts[5], "");
}

static void test_splitWithMaxParts()
{
    std::string test("abc:=:def:=:ghi:=:jkl:=:");
    std::vector<std::string> parts;
    String::Utf8::split(parts, test, ":=:", 3);
    JT_EQUAL(parts.size(), 3);
    JT_EQUAL(parts[0], "abc");
    JT_EQUAL(parts[1], "def");
    JT_EQUAL(parts[2], "ghi:=:jkl:=:");

    parts.clear();
    String::Utf8::split(parts, "a", ":", 2);
    JT_EQUAL(parts.size(), 1);
    JT_EQUAL(parts[0], "a");

    parts.clear();
    String::Utf8::split(parts, "a", ":", 2, String::SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts.size(), 1);
    JT_EQUAL(parts[0], "a");
}

static void test_splitEdgeCases()
{
    std::vector<std::string> parts;

    String::Utf8::split(parts, "", ":");
    JT_EQUAL(parts.size(), 1);
    JT_EQUAL(parts[0], "");

    parts.clear();
    String::Utf8::split(parts, "", ":", 0, String::SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts.size(), 0);

    parts.clear();
    String::Utf8::split(parts, ":", ":");
    JT_EQUAL(parts.size(), 2);
    JT_EQUAL(parts[0], "");
    JT_EQUAL(parts[1], "");

    parts.clear();
    String::Utf8::split(parts, ":", ":", 0, String::SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts.size(), 0);

    parts.clear();
    String::Utf8::split(parts, "a", ":");
    JT_EQUAL(parts.size(), 1);
    JT_EQUAL(parts[0], "a");

    parts.clear();
    String::Utf8::split(parts, "a", ":", 0, String::SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts.size(), 1);
    JT_EQUAL(parts[0], "a");
}

JT_TEST(test_splitWithoutSepIgnoreEmpty,
             test_splitWithoutSep,
             test_splitWithMaxParts,
             test_splitEdgeCases);
