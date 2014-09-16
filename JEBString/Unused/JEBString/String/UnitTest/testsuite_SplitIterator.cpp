#include "../Generic/SplitIterator.hpp"

#include <JEBTest/JEBTest.hpp>
#include "../Generic/Finder.hpp"

using namespace JEB::String;

static void test_SplitIterator()
{
    typedef std::string::const_iterator StrIt;
    typedef Generic::FirstFinder<StrIt, std::equal_to<uint32_t>> Finder;
    typedef Generic::SplitIterator<StrIt, Finder> Iterator;
    std::string str = "abra-:-ka-:-dabra";
    std::string token = "-:-";
    Iterator it(str.begin(), str.end(),
                Finder(token.begin(), token.end(), std::equal_to<uint32_t>()));
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "abra");
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "ka");
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "dabra");
    JT_ASSERT(!it.next());
    JT_ASSERT(!it.next());
}

static void test_SplitIteratorEmpties()
{
    typedef std::string::const_iterator StrIt;
    typedef Generic::FirstFinder<StrIt, std::equal_to<uint32_t>> Finder;
    typedef Generic::SplitIterator<StrIt, Finder> Iterator;
    std::string str = "-:-abra-:-";
    std::string token = "-:-";
    Iterator it(str.begin(), str.end(),
                Finder(token.begin(), token.end(), std::equal_to<uint32_t>()));
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "");
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "abra");
    JT_ASSERT(it.next());
    JT_EQUAL(std::string(it.begin(), it.end()), "");
    JT_ASSERT(!it.next());
}

static void test_Bug()
{
    typedef std::string::const_iterator StrIt;
    typedef Generic::FirstFinder<StrIt, std::equal_to<uint32_t>> Finder;
    typedef Generic::SplitIterator<StrIt, Finder> Iterator;
    std::string str = "abra";
    std::string token = "-:-";
    Iterator it(str.begin(), str.end(),
                Finder(token.begin(), token.end(), std::equal_to<uint32_t>()));
    JT_ASSERT(it.next());
    JT_ASSERT(!it.next());
    JT_ASSERT(it.eof());
}

JT_TEST(test_SplitIterator, test_SplitIteratorEmpties, test_Bug);
