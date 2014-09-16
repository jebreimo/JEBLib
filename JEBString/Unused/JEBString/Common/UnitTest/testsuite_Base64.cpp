#include "../Base64.hpp"
#include <iterator>
#include <JEBTest/JEBTest.hpp>

using namespace JEB;

// ABCD EFGH IJKL MNOP
// QRST UVWX YZab cdef
// ghij klmn opqr stuv
// wxyz 0123 4567 89+/

static void test_Sizes()
{
    JT_EQUAL(Base64::encodedSize(0), 0);
    JT_EQUAL(Base64::encodedSize(1), 4);
    JT_EQUAL(Base64::encodedSize(2), 4);
    JT_EQUAL(Base64::encodedSize(3), 4);
    JT_EQUAL(Base64::encodedSize(4), 8);
    JT_EQUAL(Base64::decodedSize(0), 0);
    JT_EQUAL(Base64::decodedSize(1), 3);
    JT_EQUAL(Base64::decodedSize(2), 3);
    JT_EQUAL(Base64::decodedSize(3), 3);
    JT_EQUAL(Base64::decodedSize(4), 3);
    JT_EQUAL(Base64::decodedSize(5), 6);
}

static void test_Encode()
{
    Base64 b64;
    JT_EQUAL(b64[0], 'A');
    JT_EQUAL(b64[63], '/');
    std::string str = "ABC";
    char out[5] = {0};
    JT_EQUAL(b64.encode(str.begin(), str.end(), out), out + 4);
    // 01000001 01000010 01000011
    // 010000 010100 001001 000011
    JT_EQUAL(std::string(out), "QUJD");
}

static void test_Decode()
{
    Base64 b64;
    std::string str = "AVq/";
    char out[4] = {0};
    JT_EQUAL(b64.decode(str.begin(), str.end(), out), out + 3);
    // 000000 010101 101010 111111
    // 00000001 01011010 10111111
    JT_EQUAL(std::string(out), "\x01Z\xBF");
}

static void test_TooShortCoding()
{
    Base64 b64;
    std::string str = "h";
    char out[4] = {0};
    JT_EQUAL(b64.decode(str.begin(), str.end(), out), out + 3);
    // 000000 010101 101010 111111
    // 00000001 01011010 10111111
    JT_EQUAL(std::string(out), "\x84\0\0");
}

/** Test char values above 0x7F. These were handled incorrectly at one point.
 */
static void test_Negative()
{
    Base64 b64;
    std::string original = "\xD0\xF4\xC2";
    std::string encoded;
    b64.encode(original.begin(), original.end(), std::back_inserter(encoded));
    JT_EQUAL(encoded.size(), 4);
    std::string decoded;
    b64.decode(encoded.begin(), encoded.end(), std::back_inserter(decoded));
    JT_EQUAL(decoded.size(), 3);
    JT_EQUAL(decoded, original);
}

JT_TEST(test_Sizes,
        test_Encode,
        test_Decode,
        test_TooShortCoding,
        test_Negative);
