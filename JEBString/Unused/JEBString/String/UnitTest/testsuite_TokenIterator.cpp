#include "../Generic/TokenIterator.hpp"

#include <JEBTest/JEBTest.hpp>
#include "../Generic/Finder.hpp"

using namespace JEB::String;

static void test_TokenIterator()
{
    typedef std::string::const_iterator StrIt;
    typedef Generic::FirstFinder<StrIt, std::equal_to<uint32_t>> Finder;
    typedef Generic::TokenIterator<StrIt, Finder> Iterator;
    std::string str = "abra-:-ka-:-dabra";
    std::string token = "-:-";
    Iterator it(str.begin(), str.end(),
                Finder(token.begin(), token.end(), std::equal_to<uint32_t>()));
    JT_ASSERT(it.next());
    JT_ASSERT(it.next());
    JT_ASSERT(!it.next());
}

JT_TEST(test_TokenIterator);
