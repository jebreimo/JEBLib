#include "JEBString/Paths/UnixPathTokenizer.hpp"
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
    auto tokenizer = UnixPathTokenizer{};
    auto pathRange = makeRange(path);
    auto token = tokenizer.next(pathRange);
    JT_EQUAL(fromRange<std::string>(token.first), expectedToken);
    JT_EQUAL(fromRange<std::string>(pathRange), expectedRemainder);
    JT_EQUAL(token.second, expectedType);
}

void test_nextToken()
{
    JT_CALL(testNextToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testNextToken("/", "/", "", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("/a", "/", "a", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("//", "/", "/", PathTokenType::PathSeparator));
    JT_CALL(testNextToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc/", "abc", "/", PathTokenType::PathName));
    JT_CALL(testNextToken("abc.def", "abc.def", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc.def/", "abc.def", "/", PathTokenType::PathName));
    JT_CALL(testNextToken("abc def", "abc def", "", PathTokenType::PathName));
    JT_CALL(testNextToken("abc def/", "abc def", "/", PathTokenType::PathName));
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
    JT_CALL(testPrevToken("", "", "", PathTokenType::EmptyPath));
    JT_CALL(testPrevToken("/", "/", "", PathTokenType::PathRoot));
    JT_CALL(testPrevToken("abc/", "/", "abc", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken("abc/", "/", "abc", PathTokenType::PathSeparator));
    JT_CALL(testPrevToken("abc", "abc", "", PathTokenType::PathName));
    JT_CALL(testPrevToken("/abc", "abc", "/", PathTokenType::PathName));
}

JT_SUBTEST("Paths", test_nextToken, test_prevToken);

}
