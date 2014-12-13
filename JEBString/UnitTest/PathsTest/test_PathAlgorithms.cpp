#include "JEBString/Paths/PathAlgorithms.hpp"
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include <JEBTest/JEBTest.hpp>
#include "JEBString/Paths/UnixPathTokenizer.hpp"
#include "JEBString/Paths/WindowsPathTokenizer.hpp"

namespace {

using JEBBase::Ranges::Range;
using JEBBase::Ranges::makeRange;
using namespace JEBString::Paths;

std::string str(Range<const char*> r)
{
    return std::string(begin(r), end(r));
}

void test_baseName_ux()
{
    UnixPathTokenizer tok;
    JT_EQUAL(str(baseName(tok, makeRange("/abra/kadabra.txt"))),
             "kadabra.txt");
    JT_EQUAL(str(baseName(tok, makeRange("kadabra"))),
             "kadabra");
    JT_EQUAL(str(baseName(tok, makeRange("/abra/kadabra/"))),
             "");
}

void test_baseName_win()
{
    WindowsPathTokenizer tok;
    JT_EQUAL(str(baseName(tok, makeRange("C:\\abra\\kadabra.txt"))),
             "kadabra.txt");
    JT_EQUAL(str(baseName(tok, makeRange("C:\\abra\\kadabra\\"))),
             "");
}

void test_commonPath_ux()
{
    UnixPathTokenizer tok;
    auto cp = commonPath(tok,
                         makeRange("/abra/kadabra/hokus/pokus"),
                         makeRange("/abra/kadabra/hokius/pokus"));
    JT_EQUAL(str(cp.first), "/abra/kadabra/");
    JT_EQUAL(str(cp.second), "/abra/kadabra/");
    cp = commonPath(tok, makeRange("hokus/pokus"),
                         makeRange("hokius/pokus"));
    JT_EQUAL(str(cp.first), "");
    JT_EQUAL(str(cp.second), "");
}

void test_commonPath_win()
{
    WindowsPathTokenizer tok;
    auto cp = commonPath(tok,
                         makeRange("C:\\abra\\kadabra\\hokus\\pokus"),
                         makeRange("C:\\abra\\kadabra\\hokius\\pokus"));
    JT_EQUAL(str(cp.first), "C:\\abra\\kadabra\\");
    JT_EQUAL(str(cp.second), "C:\\abra\\kadabra\\");
}

void test_dirName_ux()
{
    UnixPathTokenizer tok;
    JT_EQUAL(str(dirName(tok, makeRange("/abra/kadabra.txt"))), "/abra");
    JT_EQUAL(str(dirName(tok, makeRange("/abra/"))), "/abra");
    JT_EQUAL(str(dirName(tok, makeRange("/abra"))), "/");
    JT_EQUAL(str(dirName(tok, makeRange("/"))), "/");
    JT_EQUAL(str(dirName(tok, makeRange("abra"))), "");
}

void test_dirName_win()
{
    WindowsPathTokenizer tok;
    JT_EQUAL(str(dirName(tok, makeRange("C:\\abra\\kadabra.txt"))),
             "C:\\abra");
    JT_EQUAL(str(dirName(tok, makeRange("C:\\abra\\"))), "C:\\abra");
    JT_EQUAL(str(dirName(tok, makeRange("C:\\abra"))), "C:");
    JT_EQUAL(str(dirName(tok, makeRange("C:\\"))), "C:");
    JT_EQUAL(str(dirName(tok, makeRange("abra"))), "");
    JT_EQUAL(str(dirName(tok, makeRange("\\abra\\kadabra.txt"))), "\\abra");
    JT_EQUAL(str(dirName(tok, makeRange("\\abra\\"))), "\\abra");
    JT_EQUAL(str(dirName(tok, makeRange("\\abra"))), "\\");
    JT_EQUAL(str(dirName(tok, makeRange("\\"))), "\\");
}

JT_SUBTEST("Paths",
           test_baseName_ux,
           test_baseName_win,
           test_commonPath_ux,
           test_commonPath_win,
           test_dirName_ux,
           test_dirName_win);

}
