#include "JEBIO/Streams/StreamJoin.hpp"
#include <sstream>

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBIO;

static void test_join()
{
    const char* strs[] = {"alpha", "bravo", "charlie", "delta", "echo"};
    std::ostringstream ss;
    ss << "Strings: " << join(std::begin(strs), std::end(strs), ", ");
    JT_EQUAL(ss.str(), "Strings: alpha, bravo, charlie, delta, echo");
}

JT_SUBTEST("Streams", test_join);

}
