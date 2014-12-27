#include "JEBIO/Paths/WindowsPaths.hpp"

#include <vector>
#include <JEBTest/JEBTest.hpp>

using namespace JEBIO;

namespace
{

template <typename T, typename U>
std::pair<std::string, std::string> stringPair(T&& first, U&& second)
{
    return std::make_pair<std::string, std::string>(first, second);
}

void test_split()
{
    JT_EQUAL(Windows::split("a\\b"), stringPair("a", "b"));
    JT_EQUAL(Windows::split("a\\b\\"), stringPair("a\\b", ""));
    JT_EQUAL(Windows::split("\\a"), stringPair("\\", "a"));
    JT_EQUAL(Windows::split("\\a\\"), stringPair("\\a", ""));
    JT_EQUAL(Windows::split("a"), stringPair("", "a"));
    JT_EQUAL(Windows::split("\\a\\b\\c\\d"), stringPair("\\a\\b\\c", "d"));
    JT_EQUAL(Windows::split("c:\\a"), stringPair("c:\\", "a"));
    JT_EQUAL(Windows::split("c:a"), stringPair("c:", "a"));
    JT_EQUAL(Windows::split("\\\\abra\\b"), stringPair("\\\\abra", "b"));
    JT_EQUAL(Windows::split("\\\\abra"), stringPair("\\\\abra", ""));
    JT_EQUAL(Windows::split("c:\\"), stringPair("c:\\", ""));
    JT_EQUAL(Windows::split("c:"), stringPair("c:", ""));
}

void testSplitExtension(const std::string& str,
                        const std::string& expFirst,
                        const std::string& expSecond)
{
    JT_EQUAL(Windows::splitExtension(str), std::make_pair(expFirst, expSecond));
    JT_EQUAL(Windows::removeExtension(str), expFirst);
    JT_EQUAL(Windows::extension(str), expSecond);
}

void test_splitExtension()
{
    JT_CALL(testSplitExtension("", "", ""));
    JT_CALL(testSplitExtension(".", ".", ""));
    JT_CALL(testSplitExtension("\\", "\\", ""));
    JT_CALL(testSplitExtension("\\.", "\\.", ""));
    JT_CALL(testSplitExtension("abc.txt", "abc", ".txt"));
    JT_CALL(testSplitExtension("abc.txt\\foo.txt", "abc.txt\\foo", ".txt"));
    JT_CALL(testSplitExtension("abc.txt\\foo.2010.txt", "abc.txt\\foo.2010", ".txt"));
    JT_CALL(testSplitExtension(".txt", ".txt", ""));
    JT_CALL(testSplitExtension("\\.txt", "\\.txt", ""));
    JT_CALL(testSplitExtension("\\home\\.txt", "\\home\\.txt", ""));
    JT_CALL(testSplitExtension("abc.txt\\foo", "abc.txt\\foo", ""));
    JT_CALL(testSplitExtension("abc.txt\\foo.", "abc.txt\\foo", "."));
    JT_CALL(testSplitExtension("\\abc.txt\\file.with_long_extension",
                               "\\abc.txt\\file", ".with_long_extension"));
    JT_CALL(testSplitExtension("C:.txt", "C:.txt", ""));
    JT_CALL(testSplitExtension("C:.", "C:.", ""));
}

JT_SUBTEST("Paths",
           // test_baseName,
           // test_commonPath,
           // test_dirName,
           // test_join,
           // test_normalize,
           // test_relativePath,
           // test_replaceExtension,
           test_split,
           test_splitExtension
           );
}
