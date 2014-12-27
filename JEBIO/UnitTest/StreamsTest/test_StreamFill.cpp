#include "JEBIO/Streams/StreamFill.hpp"
#include <sstream>

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBIO;

static void test_fill()
{
    std::ostringstream ss;
    ss << "Hello" << spaces(4) << "Jan Erik";
    JT_EQUAL(ss.str(), "Hello    Jan Erik");
    std::wostringstream ws;
    ws << L"Hello" << spaces(4) << L"Jan Erik";
    JT_EQUAL(ws.str(), L"Hello    Jan Erik");
    std::wostringstream ws2;
    ws2 << L"Hello" << fill(3, 13) << L"Jan Erik";
    JT_EQUAL(ws2.str(), L"Hello131313Jan Erik");
}

JT_SUBTEST("Streams", test_fill);

}
