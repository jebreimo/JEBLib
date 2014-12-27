#include "JEBIO/Paths/PathAlgorithms.hpp"
#include <JEBTest/JEBTest.hpp>
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include "JEBIO/Paths/UnixPathTokenizer.hpp"
#include "JEBIO/Paths/WindowsPathTokenizer.hpp"

namespace {

using JEBBase::Ranges::Range;
using JEBBase::Ranges::fromRange;
using JEBBase::Ranges::makeRange;
using namespace JEBIO;

template <typename It>
std::string str(Range<It> r)
{
    return fromRange<std::string>(r);
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

template <typename Tokenizer>
void testExtension(const std::string& path,
                   const std::string& expectedExtension,
                   const std::string& expectedRemainder)
{
    auto pathRange = makeRange(path);
    JT_EQUAL(str(extension(Tokenizer(), pathRange)), expectedExtension);
    JT_EQUAL(str(pathRange), expectedRemainder);
}

void test_extension_ux()
{
    JT_CALL(testExtension<UnixPathTokenizer>("/a/b/cdef.ghij",
                                             ".ghij", "/a/b/cdef"));
    JT_CALL(testExtension<UnixPathTokenizer>("/a/b/.ghij",
                                             "", "/a/b/.ghij"));
    JT_CALL(testExtension<UnixPathTokenizer>("/a/b.cd/ghij",
                                             "", "/a/b.cd/ghij"));
}

JT_SUBTEST("Paths",
           test_baseName_ux,
           test_baseName_win,
           test_commonPath_ux,
           test_commonPath_win,
           test_dirName_ux,
           test_dirName_win,
           test_extension_ux);

}
