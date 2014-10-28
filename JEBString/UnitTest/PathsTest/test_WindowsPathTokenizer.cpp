#include "JEBString/Paths/WindowsPathTokenizer.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBString::Paths;
using JEBBase::Ranges::makeRange;
using JEBBase::Ranges::fromRange;

void testNextToken(const std::string& path,
                   const std::string& expectedToken,
                   const std::string& expectedRemainder,
                   PathTokenType expectedType)
{
    auto tokenizer = WindowsPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.next(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_nextToken()
{
    JT_CALL(testNextToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testNextToken("\\", "\\", "", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("\\:", "\\", ":", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("\\a", "\\", "a", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("\\\\", "\\", "\\", PathTokenType::PathSeparator));
    JT_CALL(testNextToken(":", ":", "", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextToken(":\\", ":", "\\", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextToken(":abc", ":", "abc", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextToken("::", ":", ":", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc\\", "abc", "\\", PathTokenType::PathName));
    JT_CALL(testNextToken("abc:", "abc", ":", PathTokenType::PathName));
    JT_CALL(testNextToken("abc.def", "abc.def", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc.def\\", "abc.def", "\\", PathTokenType::PathName));
    JT_CALL(testNextToken("abc def", "abc def", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc def\\", "abc def", "\\", PathTokenType::PathName));
}

void testPrevToken(const std::string& path,
                   const std::string& expectedToken,
                   const std::string& expectedRemainder,
                   PathTokenType expectedType)
{
    auto tokenizer = WindowsPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.prev(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_prevToken()
{
    JT_CALL(testPrevToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testPrevToken("\\", "\\", "", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken(":\\", "\\", ":", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken("a\\", "\\", "a", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken("\\\\", "\\", "\\", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken(":", ":", "", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevToken("\\:", ":", "\\", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevToken("abc:", ":", "abc", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevToken("::", ":", ":", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testPrevToken("\\abc", "abc", "\\", PathTokenType::PathName));
    JT_CALL(testPrevToken("C:abc", "abc", "C:", PathTokenType::PathName));
    JT_CALL(testPrevToken("abc.def", "abc.def", "", PathTokenType::PathName));
    JT_CALL(testPrevToken("\\abc.def", "abc.def", "\\", PathTokenType::PathName));
    JT_CALL(testPrevToken("abc def", "abc def", "", PathTokenType::PathName));
    JT_CALL(testPrevToken("\\abc def", "abc def", "\\", PathTokenType::PathName));
}

void testNextSubToken(const std::string& path,
                      const std::string& expectedToken,
                      const std::string& expectedRemainder,
                      PathTokenType expectedType)
{
    auto tokenizer = WindowsPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.nextSubToken(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_nextSubToken()
{
    JT_CALL(testNextSubToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testNextSubToken("\\", "\\", "", PathTokenType::PathSeparator));
    JT_CALL(testNextSubToken("\\a", "\\", "a", PathTokenType::PathSeparator));
    JT_CALL(testNextSubToken("\\\\", "\\", "\\", PathTokenType::PathSeparator));
    JT_CALL(testNextSubToken(":", ":", "", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextSubToken(":\\", ":", "\\", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextSubToken(":abc", ":", "abc", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextSubToken("::", ":", ":", PathTokenType::PathDriveSeparator));
    JT_CALL(testNextSubToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testNextSubToken("abc\\", "abc", "\\", PathTokenType::PathName));
    JT_CALL(testNextSubToken("abc.def", "abc", ".def", PathTokenType::PathName));
    JT_CALL(testNextSubToken("abc.def\\", "abc", ".def\\", PathTokenType::PathName));
    JT_CALL(testNextSubToken("abc def", "abc def", "", PathTokenType::PathName));
    JT_CALL(testNextSubToken("abc def\\", "abc def", "\\", PathTokenType::PathName));
    JT_CALL(testNextSubToken(".", ".", "", PathTokenType::PathExtensionSeparator));
    JT_CALL(testNextSubToken(".def", ".", "def", PathTokenType::PathExtensionSeparator));
    JT_CALL(testNextSubToken(".\\", ".", "\\", PathTokenType::PathExtensionSeparator));
    JT_CALL(testNextSubToken(".:", ".", ":", PathTokenType::PathExtensionSeparator));
    JT_CALL(testNextSubToken("..", ".", ".", PathTokenType::PathExtensionSeparator));
}

void testPrevSubToken(const std::string& path,
                      const std::string& expectedToken,
                      const std::string& expectedRemainder,
                      PathTokenType expectedType)
{
    auto tokenizer = WindowsPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.prevSubToken(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_prevSubToken()
{
    JT_CALL(testPrevSubToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testPrevSubToken("\\", "\\", "", PathTokenType::PathSeparator));
    JT_CALL(testPrevSubToken("a\\", "\\", "a", PathTokenType::PathSeparator));
    JT_CALL(testPrevSubToken("\\\\", "\\", "\\", PathTokenType::PathSeparator));
    JT_CALL(testPrevSubToken(":", ":", "", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevSubToken("\\:", ":", "\\", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevSubToken("abc:", ":", "abc", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevSubToken("::", ":", ":", PathTokenType::PathDriveSeparator));
    JT_CALL(testPrevSubToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testPrevSubToken("\\abc", "abc", "\\", PathTokenType::PathName));
    JT_CALL(testPrevSubToken("abc.def", "def", "abc.", PathTokenType::PathName));
    JT_CALL(testPrevSubToken("\\abc.def", "def", "\\abc.", PathTokenType::PathName));
    JT_CALL(testPrevSubToken("abc def", "abc def", "", PathTokenType::PathName));
    JT_CALL(testPrevSubToken("\\abc def", "abc def", "\\", PathTokenType::PathName));
    JT_CALL(testPrevSubToken(".", ".", "", PathTokenType::PathExtensionSeparator));
    JT_CALL(testPrevSubToken("def.", ".", "def", PathTokenType::PathExtensionSeparator));
    JT_CALL(testPrevSubToken("\\.", ".", "\\", PathTokenType::PathExtensionSeparator));
    JT_CALL(testPrevSubToken("..", ".", ".", PathTokenType::PathExtensionSeparator));
}

JT_SUBTEST("Paths",
           test_nextToken,
           test_prevToken,
           test_nextSubToken,
           test_prevSubToken);

}
