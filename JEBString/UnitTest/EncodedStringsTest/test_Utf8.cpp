#include "JEBString/EncodedStrings/DecodeUtf8.hpp"
#include "JEBString/EncodedStrings/EncodeUtf8.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBString::EncodedStrings;

void testNextOk(const std::string& s, uint32_t expected)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), DecodeResult::Ok);
    JT_ASSERT(it == s.cend());
    JT_EQUAL(c, expected);
}

void testNextOk(const std::string& s, uint32_t expected, size_t length)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), DecodeResult::Ok);
    JT_ASSERT(it == s.begin() + length);
    JT_EQUAL(c, expected);
}

void testNextNotOk(const std::string& s, int expected)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), expected);
    JT_ASSERT(it == s.cbegin());
}

void test_nextChar()
{
    JT_CALL(testNextOk("\x01", 0x01));
    JT_CALL(testNextOk("A", 'A'));
    JT_CALL(testNextOk("\x7F", 0x7F));
    JT_CALL(testNextOk("\xC2\x80", 0x80));
    JT_CALL(testNextOk("\xDF\xBF", 0x7FF));
    JT_CALL(testNextOk("\xFB\xBF\xBF\xBF\xBF", 0x3FFFFFF));
    JT_CALL(testNextOk("\xFD\x80\x80\x80\x80\x80", 0x40000000));
    JT_CALL(testNextNotOk("\xFC\x80\x80\x80\x80\x80", DecodeResult::Invalid));
    JT_CALL(testNextOk("\xFD\xBF\xBF\xBF\xBF\xBF", 0x7FFFFFFF));
    JT_CALL(testNextOk("\xF4\x80\x80\x80\x80", 0x100000, 4));
    JT_CALL(testNextOk("\xD0\x80\x80", 0x400, 2));
    JT_CALL(testNextNotOk("", DecodeResult::EndOfString));
    JT_CALL(testNextNotOk("\xC8", DecodeResult::Incomplete | DecodeResult::EndOfString));
    JT_CALL(testNextNotOk("\x80", DecodeResult::Invalid));
    JT_CALL(testNextNotOk("\x80" "A", DecodeResult::Invalid));
    JT_CALL(testNextNotOk("\xF1\x80\x80", DecodeResult::Incomplete | DecodeResult::EndOfString));
    JT_CALL(testNextNotOk("\xF1\x80\x80" "A", DecodeResult::Incomplete));
    JT_CALL(testNextNotOk("\xFE\x80\x80\x80\x80\x80\x80", DecodeResult::Invalid));
    JT_CALL(testNextNotOk("\xFF\x80\x80\x80\x80\x80\x80\x80", DecodeResult::Invalid));
}

void testPrevNotOk(const std::string& s, unsigned expected)
{
    uint32_t c;
    auto it = s.cend();
    JT_EQUAL(prevUtf8CodePoint(c, s.cbegin(), it), expected);
    JT_ASSERT(it == s.cend());
}

void testPrevOk(const std::string& s, uint32_t expected)
{
    uint32_t c;
    auto it = s.cend();
    JT_EQUAL(prevUtf8CodePoint(c, s.cbegin(), it), DecodeResult::Ok);
    JT_ASSERT(it == s.cbegin());
    JT_EQUAL(c, expected);
}

void test_prevChar()
{
    JT_CALL(testPrevNotOk("\xC0\xBF", DecodeResult::Invalid));
    JT_CALL(testPrevOk("\x01", 0x01));
    JT_CALL(testPrevOk("A", 'A'));
    JT_CALL(testPrevOk("\x7F", 0x7F));
    JT_CALL(testPrevOk("\xC2\x80", 0x80));
    JT_CALL(testPrevOk("\xDF\xBF", 0x7FF));
    JT_CALL(testPrevOk("\xFB\xBF\xBF\xBF\xBF", 0x3FFFFFF));
    JT_CALL(testPrevOk("\xFD\x80\x80\x80\x80\x80", 0x40000000));
    JT_CALL(testPrevNotOk("\xFC\x80\x80\x80\x80\x80", DecodeResult::Invalid));
    JT_CALL(testPrevOk("\xFD\xBF\xBF\xBF\xBF\xBF", 0x7FFFFFFF));
    JT_CALL(testPrevNotOk("", DecodeResult::EndOfString));
    JT_CALL(testPrevNotOk("\x80", DecodeResult::Invalid));
    JT_CALL(testPrevNotOk("A\x80", DecodeResult::Invalid));
    JT_CALL(testPrevNotOk("\xF1\x80\x80", DecodeResult::Incomplete));
    JT_CALL(testPrevNotOk("\xF1\x80\x80\x80\x80", DecodeResult::Invalid));
    JT_CALL(testPrevNotOk("\xFF\x80\x80\x80\x80\x80\x80\x80", DecodeResult::Invalid));
    JT_CALL(testPrevNotOk("\xFE\x80\x80\x80\x80\x80\x80", DecodeResult::Invalid));
}

void test_encode()
{
    std::string s(8, ' ');
    std::string::iterator it;
    it = s.begin();
    JT_ASSERT(encodeUtf8(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    JT_ASSERT(encodeUtf8(it, s.end(), 0xFFF));
    JT_EQUAL((uint8_t)s[1], 0xE0);
    JT_EQUAL((uint8_t)s[2], 0xBF);
    JT_EQUAL((uint8_t)s[3], 0xBF);
}

JT_SUBTEST("Utf8",
           test_nextChar,
           test_prevChar,
           test_encode);
}
