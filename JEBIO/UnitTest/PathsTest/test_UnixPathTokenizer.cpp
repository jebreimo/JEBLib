#include "JEBIO/Paths/UnixPathTokenizer.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBIO;
using JEBBase::Ranges::makeRange;
using JEBBase::Ranges::fromRange;

void testNextToken(const std::string& path,
                   const std::string& expectedToken,
                   const std::string& expectedRemainder,
                   PathTokenType expectedType)
{
    auto tokenizer = UnixPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.next(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_nextToken()
{
    JT_CALL(testNextToken("", "", "", PathTokenType::Empty));
    JT_CALL(testNextToken("/", "/", "", PathTokenType::DirSeparator));
    JT_CALL(testNextToken("/a", "/", "a", PathTokenType::DirSeparator));
    JT_CALL(testNextToken("//", "/", "/", PathTokenType::DirSeparator));
    JT_CALL(testNextToken("abc", "abc", "", PathTokenType::Name));
    JT_CALL(testNextToken("abc/", "abc", "/", PathTokenType::Name));
    JT_CALL(testNextToken("abc.def", "abc.def", "", PathTokenType::Name));
    JT_CALL(testNextToken("abc.def/", "abc.def", "/", PathTokenType::Name));
    JT_CALL(testNextToken("abc def", "abc def", "", PathTokenType::Name));
    JT_CALL(testNextToken("abc def/", "abc def", "/", PathTokenType::Name));
}

void testPrevToken(const std::string& path,
                   const std::string& expectedToken,
                   const std::string& expectedRemainder,
                   PathTokenType expectedType)
{
    auto tokenizer = UnixPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.prev(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_prevToken()
{
    JT_CALL(testPrevToken("", "", "", PathTokenType::Empty));
    JT_CALL(testPrevToken("/", "/", "", PathTokenType::DirSeparator));
    JT_CALL(testPrevToken("abc/", "/", "abc", PathTokenType::DirSeparator));
    JT_CALL(testPrevToken("abc/", "/", "abc", PathTokenType::DirSeparator));
    JT_CALL(testPrevToken("abc", "abc", "", PathTokenType::Name));
    JT_CALL(testPrevToken("/abc", "abc", "/", PathTokenType::Name));
}

void testNextSubToken(const std::string& path,
                      const std::string& expectedToken,
                      const std::string& expectedRemainder,
                      PathTokenType expectedType)
{
    auto tokenizer = UnixPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.nextSubToken(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_nextSubToken()
{
    JT_CALL(testNextSubToken("", "", "", PathTokenType::Empty));
    JT_CALL(testNextSubToken("/", "/", "", PathTokenType::DirSeparator));
    JT_CALL(testNextSubToken("/a", "/", "a", PathTokenType::DirSeparator));
    JT_CALL(testNextSubToken("//", "/", "/", PathTokenType::DirSeparator));
    JT_CALL(testNextSubToken("abc", "abc", "", PathTokenType::Name));
    JT_CALL(testNextSubToken("abc/", "abc", "/", PathTokenType::Name));
    JT_CALL(testNextSubToken("abc.def", "abc", ".def", PathTokenType::Name));
    JT_CALL(testNextSubToken("abc.def/", "abc", ".def/", PathTokenType::Name));
    JT_CALL(testNextSubToken("abc def", "abc def", "", PathTokenType::Name));
    JT_CALL(testNextSubToken("abc def/", "abc def", "/", PathTokenType::Name));
    JT_CALL(testNextSubToken(".", ".", "", PathTokenType::ExtensionSeparator));
    JT_CALL(testNextSubToken(".def", ".", "def", PathTokenType::ExtensionSeparator));
    JT_CALL(testNextSubToken("./", ".", "/", PathTokenType::ExtensionSeparator));
    JT_CALL(testNextSubToken("..", ".", ".", PathTokenType::ExtensionSeparator));
}

void testPrevSubToken(const std::string& path,
                      const std::string& expectedToken,
                      const std::string& expectedRemainder,
                      PathTokenType expectedType)
{
    auto tokenizer = UnixPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.prevSubToken(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_prevSubToken()
{
    JT_CALL(testPrevSubToken("", "", "", PathTokenType::Empty));
    JT_CALL(testPrevSubToken("/", "/", "", PathTokenType::DirSeparator));
    JT_CALL(testPrevSubToken("a/", "/", "a", PathTokenType::DirSeparator));
    JT_CALL(testPrevSubToken("//", "/", "/", PathTokenType::DirSeparator));
    JT_CALL(testPrevSubToken("abc", "abc", "", PathTokenType::Name));
    JT_CALL(testPrevSubToken("/abc", "abc", "/", PathTokenType::Name));
    JT_CALL(testPrevSubToken("abc.def", "def", "abc.", PathTokenType::Name));
    JT_CALL(testPrevSubToken("/abc.def", "def", "/abc.", PathTokenType::Name));
    JT_CALL(testPrevSubToken("abc def", "abc def", "", PathTokenType::Name));
    JT_CALL(testPrevSubToken("/abc def", "abc def", "/", PathTokenType::Name));
    JT_CALL(testPrevSubToken(".", ".", "", PathTokenType::ExtensionSeparator));
    JT_CALL(testPrevSubToken("def.", ".", "def", PathTokenType::ExtensionSeparator));
    JT_CALL(testPrevSubToken("/.", ".", "/", PathTokenType::ExtensionSeparator));
    JT_CALL(testPrevSubToken("..", ".", ".", PathTokenType::ExtensionSeparator));
}

JT_SUBTEST("Paths",
           test_nextToken,
           test_prevToken,
           test_nextSubToken,
           test_prevSubToken);
}
