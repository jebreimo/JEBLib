#include "WindowsPaths.hpp"
#include <cstdint>
#include "JEBBase/Iterators/Iterators.hpp"
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include "JEBString/RawStrings/RawString.hpp"

namespace JEBIO { namespace Windows {

using JEBBase::Ranges::makeRange;
using namespace JEBString;

namespace
{
    // const char DirSep = '\\';
    static const std::string DirSepStr("\\");

    bool isDirSep(uint32_t ch)
    {
        return ch == '\\' || ch == '/';
    }

    bool isDriveSep(uint32_t ch)
    {
        return ch == ':';
    }

    bool isPathSep(uint32_t ch)
    {
        return isDirSep(ch) || isDriveSep(ch);
    }

    bool isExtensionSep(uint32_t ch)
    {
        return ch == '.';
    }

    bool isDirOrExtensionSep(uint32_t ch)
    {
        return isPathSep(ch) || isExtensionSep(ch);
    }

    bool isDriveLetter(char c)
    {
        return 'A' <= (c & 0xDF) && (c & 0xDF) <= 'Z';
    }

    template <typename FwdIt>
    bool isNetworkRoot(FwdIt first, FwdIt last)
    {
        auto it1 = std::find_if_not(first, last, isDirSep);
        if (distance(first, it1) != 2 || it1 == last)
            return false;
        return std::find_if(it1, last, isDirSep) == last;
    }

    template <typename FwdIt>
    bool isDriveRoot(FwdIt first, FwdIt last)
    {
        if (first == last || isDriveSep(*first))
            return false;
        auto ch0 = *first;
        if (++first == last)
            return isDirSep(ch0);
        if (!isDriveLetter(ch0) || !isDriveSep(*first))
            return false;
        if (++first == last)
            return true;
        if (!isDirSep(*first))
            return false;
        return ++first == last;
    }

    template <typename FwdIt>
    bool isRootPath(FwdIt first, FwdIt last)
    {
        return isDriveRoot(first, last) || isNetworkRoot(first, last);
    }
}

std::string baseName(const std::string& path)
{
    auto p = makeRange(path);
    return RawStrings::toString<char>(RawStrings::prevToken(p, isDirSep));
}

std::string extension(const std::string& path)
{
    auto it = findLastIf(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isPathSep(*it) || isPathSep(*prev(it)))
        return std::string();
    return std::string(it, end(path));
}

std::string removeExtension(const std::string& path)
{
    auto it = findLastIf(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isPathSep(*it) || isPathSep(*prev(it)))
        return path;
    return std::string(begin(path), it);
}

std::pair<std::string, std::string> split(const std::string& path)
{
    if (path.empty())
        return std::pair<std::string, std::string>();

    auto p = makeRange(path);
    auto bn = RawStrings::prevToken(p, isPathSep);
    if (empty(p) && !isPathSep(*end(p)))
        return std::make_pair(std::string(), RawStrings::toString<char>(bn));
    if (isDriveRoot(begin(p), begin(bn)))
        return std::make_pair(std::string(begin(p), begin(bn)),
                              RawStrings::toString<char>(bn));
    if (size(p) == 1 && isDirSep(front(p)))
        return std::make_pair(path, std::string());
    return std::make_pair(RawStrings::toString<char>(p),
                          RawStrings::toString<char>(bn));
}

std::pair<std::string, std::string> splitExtension(const std::string& path)
{
    auto it = findLastIf(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isPathSep(*it) || isPathSep(*prev(it)))
        return make_pair(path, std::string());
    return make_pair(std::string(begin(path), it),
                     std::string(it, end(path)));
}

}}
