#include "JEBString/EncodedStrings/DecodeUtf16.hpp"
#include "JEBString/EncodedStrings/EncodeUtf16.hpp"

#include <iterator>
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace JEBString;
using namespace JEBString::EncodedStrings;

void test_AddUtf16LE()
{
    std::wstring s;
    addUtf16LE(std::back_inserter(s), (uint32_t)'a');
    JT_EQUAL(s.size(), 1);
    JT_EQUAL(s[0], 'a');
    s.clear();
    addUtf16LE(std::back_inserter(s), 0x10001ul);
    JT_EQUAL(s.size(), 2);
    JT_EQUAL(s[0], 0xD800);
    JT_EQUAL(s[1], 0xDC01);
}

void test_EncodeUtf16()
{
    std::string s(8, ' ');
    auto it = s.begin();
    JT_ASSERT(encodeUtf16(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], 'A');
    JT_EQUAL(s[1], '\0');
    it = s.begin();
    JT_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], '\0');
    JT_EQUAL(s[1], 'A');
    it = s.begin();
    JT_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], 'A');
    JT_EQUAL(s[1], '\0');
    JT_ASSERT(encodeUtf16(it, s.end(), 0x10000));
    JT_EQUAL(std::distance(s.begin(), it), 6);
    JT_EQUAL(s[2], 0x00);
    JT_EQUAL((uint8_t)s[3], 0xD8);
    JT_EQUAL(s[4], 0x00);
    JT_EQUAL((uint8_t)s[5], 0xDC);
}

void test_EncodeWUtf16()
{
    std::wstring s(8, ' ');
    auto it = s.begin();
    JT_ASSERT(encodeUtf16(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    it = s.begin();
    JT_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A' << 8);
    it = s.begin();
    JT_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    JT_ASSERT(encodeUtf16(it, s.end(), 0x10000));
    JT_EQUAL(std::distance(s.begin(), it), 3);
    JT_EQUAL(s[1], 0xD800);
    JT_EQUAL(s[2], 0xDC00);
}

inline void testNextUtf16LEChar(const char*& it, const char* end, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(nextUtf16LECodePoint(c, it, end), DecodeResult::Ok);
    JT_EQUAL(c, expected);
}

inline void testNextUtf16BEChar(const char*& it, const char* end, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(nextUtf16BECodePoint(c, it, end), DecodeResult::Ok);
    JT_EQUAL(c, expected);
}

void test_NextUtf16LECharacter()
{
    uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF, 0xDFFF, 0xE000};

    auto it = (const char*)std::begin(s);
    auto end = (const char*)std::end(s);
    JT_CALL(testNextUtf16LEChar(it, end, 'N'));
    JT_CALL(testNextUtf16LEChar(it, end, 'a'));
    JT_CALL(testNextUtf16LEChar(it, end, 't'));
    JT_CALL(testNextUtf16LEChar(it, end, 0xD7FF));
    JT_CALL(testNextUtf16LEChar(it, end, 0x10000));
    JT_CALL(testNextUtf16LEChar(it, end, 0x10FFFF));
    JT_CALL(testNextUtf16LEChar(it, end, 0xE000));
    JT_ASSERT(it == end);
}

void test_NextUtf16BECharacter()
{
    unsigned char s[] = {0, 'N',
                         0, 'a',
                         0, 't',
                         0xD7, 0xFF,
                         0xD8, 0x00, 0xDC, 0x00,
                         0xDB, 0xFF, 0xDF, 0xFF,
                         0xE0, 0x00};
    auto it = (const char*)std::begin(s);
    auto end = (const char*)std::end(s);
    JT_CALL(testNextUtf16BEChar(it, end, 'N'));
    JT_CALL(testNextUtf16BEChar(it, end, 'a'));
    JT_CALL(testNextUtf16BEChar(it, end, 't'));
    JT_CALL(testNextUtf16BEChar(it, end, 0xD7FF));
    JT_CALL(testNextUtf16BEChar(it, end, 0x10000));
    JT_CALL(testNextUtf16BEChar(it, end, 0x10FFFF));
    JT_CALL(testNextUtf16BEChar(it, end, 0xE000));
    JT_ASSERT(it == end);
}

template <typename FwdIt>
inline void testPrevUtf16LEChar(FwdIt begin, FwdIt& it, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(prevUtf16LECodePoint(c, begin, it), DecodeResult::Ok);
    JT_EQUAL(c, expected);
}

void test_PrevUtf16LECharacter()
{
    uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF, 0xDFFF, 0xE000};

    auto begin = std::begin(s);
    auto it = std::end(s);
    JT_CALL(testPrevUtf16LEChar(begin, it, 0xE000));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0x10FFFF));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0x10000));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0xD7FF));
    JT_CALL(testPrevUtf16LEChar(begin, it, 't'));
    JT_CALL(testPrevUtf16LEChar(begin, it, 'a'));
    JT_CALL(testPrevUtf16LEChar(begin, it, 'N'));
    JT_ASSERT(it == begin);
}

JT_SUBTEST("Utf16",
           test_AddUtf16LE,
           test_EncodeUtf16,
           test_EncodeWUtf16,
           test_NextUtf16LECharacter,
           test_NextUtf16BECharacter,
           test_PrevUtf16LECharacter);
}
