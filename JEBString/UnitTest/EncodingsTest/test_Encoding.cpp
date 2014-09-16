#include "JEBString/Encodings/Encoding.hpp"

#include <sstream>
#include <JEBTest/JEBTest.hpp>

using namespace JEBString;
using namespace JEBString::Encodings;

static void test_FromName()
{
    JT_EQUAL(encodingFromName("UTF8"), Encoding::Utf8);
    JT_EQUAL(encodingFromName("UTF-8"), Encoding::Utf8);
    JT_EQUAL(encodingFromName("UTF-16"), Encoding::Utf16);
    JT_EQUAL(encodingFromName("Utf-16bE"), Encoding::Utf16BE);
    JT_EQUAL(encodingFromName("Utf32Le"), Encoding::Utf32LE);
    JT_EQUAL(encodingFromName("Kjell"), Encoding::Unknown);
}

static void test_FromBom()
{
    JT_EQUAL(encodingFromByteOrderMark("\xEF\xBB\xBF""Abrakadabra"),
             Encoding::Utf8);
}

static void test_ReadEncoding()
{
    std::stringstream ss;
    ss << "\xEF\xBB\xBF" " Abrakadabra hokus pokus filiokus";
    std::string s;
    Encoding_t enc = readEncoding(ss);
    JT_EQUAL(enc, Encoding::Utf8);
    JT_EQUAL(ss.tellg(), (std::streamoff)3);
}

JT_SUBTEST("Encodings", test_FromName, test_FromBom, test_ReadEncoding);
