#include "JEBIO/Paths/UnixPaths.hpp"

#include <vector>
#include <JEBTest/JEBTest.hpp>

using namespace JEBIO;

namespace
{
void test_baseName()
{
    JT_EQUAL(Unix::baseName("bar.exe"), "bar.exe");
    JT_EQUAL(Unix::baseName("foo/bar.exe"), "bar.exe");
    JT_EQUAL(Unix::baseName("/foo/baz/bar.exe"), "bar.exe");
    JT_EQUAL(Unix::baseName("foo/"), "");
    JT_EQUAL(Unix::baseName("/foo/baz/"), "");
}

void test_commonPath()
{
    JT_EQUAL(Unix::commonPath("/a/b/c/a", "/a/b/c/c"), "/a/b/c/");
    JT_EQUAL(Unix::commonPath("/a/b/c/a", "/a/b/b/c"), "/a/b/");
    JT_EQUAL(Unix::commonPath("/aaa/bbb/ccc", "/aaa/bb2/ccc"), "/aaa/");
    JT_EQUAL(Unix::commonPath("/aaabbb/ccc", "/aaabb2/ccc"), "/");
    JT_EQUAL(Unix::commonPath("aaabbb/ccc", "aaabb2/ccc"), "");
    JT_EQUAL(Unix::commonPath("/aaabbb/ccc", "aaabb2/ccc"), "");
    JT_EQUAL(Unix::commonPath("aaabbb/ccc", "/aaabb2/ccc"), "");
    JT_EQUAL(Unix::commonPath("a/b/c", "/a/b/c"), "");
    JT_EQUAL(Unix::commonPath("a/b/c", ""), "");
    JT_EQUAL(Unix::commonPath("", ""), "");
    JT_EQUAL(Unix::commonPath("/a/b/", "/a/b/"), "/a/b/");
    JT_EQUAL(Unix::commonPath("/a/b/", "/a/b//"), "/a/b/");
    JT_EQUAL(Unix::commonPath("/a/b//", "/a/b/"), "/a/b/");
    JT_EQUAL(Unix::commonPath("/a/b/", "/a/b/c"), "/a/b/");
    JT_EQUAL(Unix::commonPath("/a/b/c", "/a/b/"), "/a/b/");
}

void test_dirName()
{
    JT_EQUAL(Unix::dirName("/foo/"), "/foo");
    JT_EQUAL(Unix::dirName("/foo"), "/");
    JT_EQUAL(Unix::dirName("bar.exe"), "");
    JT_EQUAL(Unix::dirName("foo/bar.exe"), "foo");
    JT_EQUAL(Unix::dirName("/foo/baz/bar.exe"), "/foo/baz");
    JT_EQUAL(Unix::dirName("foo/"), "foo");
    JT_EQUAL(Unix::dirName("/foo/baz/"), "/foo/baz");
}

void test_extension()
{
    JT_EQUAL(Unix::extension("foo.exe"), ".exe");
}

void test_isAbsPath()
{
    JT_ASSERT(Unix::isAbsPath("/foo"));
    JT_ASSERT(Unix::isAbsPath("/foo/bar"));
    JT_ASSERT(!Unix::isAbsPath("./foo/bar"));
    JT_ASSERT(!Unix::isAbsPath("foo/bar"));
}

void test_join()
{
    JT_EQUAL(Unix::join("a/", "/b"), "a/b");
    JT_EQUAL(Unix::join("a", "/b"), "a/b");
    JT_EQUAL(Unix::join("a/", "b"), "a/b");
    JT_EQUAL(Unix::join("a", "b"), "a/b");
    JT_EQUAL(Unix::join("", "/b"), "/b");
    JT_EQUAL(Unix::join("a/", ""), "a/");
    JT_EQUAL(Unix::join("a", ""), "a");
    JT_EQUAL(Unix::join("", "b"), "b");
    JT_EQUAL(Unix::join("", ""), "");
}

void test_normalize()
{
    JT_EQUAL(Unix::normalize("./bar/"), "bar");
    JT_EQUAL(Unix::normalize("./bar/baz"), "bar/baz");
    JT_EQUAL(Unix::normalize("/bar/."), "/bar");
    JT_EQUAL(Unix::normalize("/bar/./baz"), "/bar/baz");
    JT_EQUAL(Unix::normalize("/foo/bar/"), "/foo/bar");
    JT_EQUAL(Unix::normalize("/foo/../bar/baz"), "/bar/baz");
    JT_EQUAL(Unix::normalize("foo/bar"), "foo/bar");
    JT_EQUAL(Unix::normalize("../bar"), "../bar");
    JT_EQUAL(Unix::normalize("/../bar"), "/bar");
    JT_EQUAL(Unix::normalize("../../foo/../bar"), "../../bar");
    JT_EQUAL(Unix::normalize("./."), ".");
    JT_EQUAL(Unix::normalize("./.."), "..");
    JT_EQUAL(Unix::normalize("a/.."), ".");
    JT_EQUAL(Unix::normalize("a/b/../../.."), "..");
    JT_EQUAL(Unix::normalize("foo//bar"), "foo/bar");
    JT_EQUAL(Unix::normalize("foo///bar"), "foo/bar");
}

void test_relativePath()
{
    JT_EQUAL(Unix::relativePath("/a/b/c/d", "/a/b/d/e"), "../../d/e");
    JT_EQUAL(Unix::relativePath("/a/b/c/d", "a/b/d/e"), "a/b/d/e");
    JT_EQUAL(Unix::relativePath("/a/b/c/d", "a/b/../d"), "a/d");
    JT_EQUAL(Unix::relativePath("/a/b/c/d", "/a/b/../d"), "../../../d");
}

void test_removeExtension()
{
    JT_EQUAL(Unix::removeExtension("abra.jpeg"), "abra");
    JT_EQUAL(Unix::removeExtension("/foo/bar/abra.jpeg"), "/foo/bar/abra");
    JT_EQUAL(Unix::removeExtension("/foo/bar/.jpeg"), "/foo/bar/.jpeg");
    JT_EQUAL(Unix::removeExtension("/foo/bar/jpeg"), "/foo/bar/jpeg");
    JT_EQUAL(Unix::removeExtension("/foo/bar/jpeg/"), "/foo/bar/jpeg/");
    JT_EQUAL(Unix::removeExtension(".jpeg"), ".jpeg");
    JT_EQUAL(Unix::removeExtension("/jpeg"), "/jpeg");
}

void test_replaceExtension()
{
    JT_EQUAL(Unix::replaceExtension("abra.jpeg", ".bmp"), "abra.bmp");
}

template <typename T, typename U>
std::pair<std::string, std::string> stringPair(T&& first, U&& second)
{
    return std::make_pair<std::string, std::string>(first, second);
}

void test_split()
{
    JT_EQUAL(Unix::split(""), stringPair("", ""));
    JT_EQUAL(Unix::split("a/b"), stringPair("a", "b"));
    JT_EQUAL(Unix::split("a/b/"), stringPair("a/b", ""));
    JT_EQUAL(Unix::split("/a"), stringPair("/", "a"));
    JT_EQUAL(Unix::split("/a/"), stringPair("/a", ""));
    JT_EQUAL(Unix::split("a"), stringPair("", "a"));
    JT_EQUAL(Unix::split("/a/b/c/d"), stringPair("/a/b/c", "d"));
}

void testSplitExtension(const std::string& str,
                        const std::string& expFirst,
                        const std::string& expSecond)
{
    JT_EQUAL(Unix::splitExtension(str), std::make_pair(expFirst, expSecond));
    JT_EQUAL(Unix::removeExtension(str), expFirst);
    JT_EQUAL(Unix::extension(str), expSecond);
}

void test_splitExtension()
{
    JT_CALL(testSplitExtension("", "", ""));
    JT_CALL(testSplitExtension(".", ".", ""));
    JT_CALL(testSplitExtension("/", "/", ""));
    JT_CALL(testSplitExtension("/.", "/.", ""));
    JT_CALL(testSplitExtension("abc.txt", "abc", ".txt"));
    JT_CALL(testSplitExtension("abc.txt/foo.txt", "abc.txt/foo", ".txt"));
    JT_CALL(testSplitExtension("abc.txt/foo.2010.txt", "abc.txt/foo.2010",
                               ".txt"));
    JT_CALL(testSplitExtension(".txt", ".txt", ""));
    JT_CALL(testSplitExtension("/.txt", "/.txt", ""));
    JT_CALL(testSplitExtension("/home/.txt", "/home/.txt", ""));
    JT_CALL(testSplitExtension("abc.txt/foo", "abc.txt/foo", ""));
    JT_CALL(testSplitExtension("abc.txt/foo.", "abc.txt/foo", "."));
    JT_CALL(testSplitExtension("/abc.txt/file.with_long_extension",
                               "/abc.txt/file", ".with_long_extension"));
}

void test_splitPath()
{
    auto parts1 = Unix::splitPath("/foo/faa/fee");
    JT_EQUAL(parts1.size(), 4);
    JT_EQUAL(parts1[0], "");
    JT_EQUAL(parts1[1], "foo");
    JT_EQUAL(parts1[2], "faa");
    JT_EQUAL(parts1[3], "fee");
    auto parts2 = Unix::splitPath("foo/faa/fee.bar");
    JT_EQUAL(parts2.size(), 3);
    JT_EQUAL(parts2[0], "foo");
    JT_EQUAL(parts2[1], "faa");
    JT_EQUAL(parts2[2], "fee.bar");
    auto parts3 = Unix::splitPath("//foo//./faa/fee/");
    JT_EQUAL(parts3.size(), 5);
    JT_EQUAL(parts3[0], "");
    JT_EQUAL(parts3[1], "foo");
    JT_EQUAL(parts3[2], ".");
    JT_EQUAL(parts3[3], "faa");
    JT_EQUAL(parts3[4], "fee");
}

JT_SUBTEST("Paths",
           test_baseName,
           test_commonPath,
           test_dirName,
           test_extension,
           test_isAbsPath,
           test_join,
           test_normalize,
           test_relativePath,
           test_removeExtension,
           test_replaceExtension,
           test_split,
           test_splitExtension,
           test_splitPath);
}
