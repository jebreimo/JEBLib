#include "UnixPaths.hpp"
#include <cstdint>
#include <JEBBase/Algorithms/Algorithms.hpp>
#include "JEBString/RawStrings/RawString.hpp"

namespace JEBString { namespace Paths { namespace Unix {

using JEBBase::Ranges::makeRange;

namespace
{
    const char DirSep = '/';
    static const std::string DirSepStr(1, DirSep);
    const char CurrentDir[] = ".";
    auto CurrentDirRange = makeRange(CurrentDir);
    const char ParentDir[] = "..";
    auto ParentDirRange = makeRange(ParentDir);
    bool isDirSep(uint32_t ch) {return ch == DirSep;}
    bool isExtensionSep(uint32_t ch) {return ch == '.';}

    bool isDirOrExtensionSep(uint32_t ch)
    {
        return isDirSep(ch) || isExtensionSep(ch);
    }
}

std::string baseName(const std::string& path)
{
    auto p = makeRange(path);
    return RawStrings::toString<char>(RawStrings::prevToken(p, isDirSep));
}

std::string commonPath(const std::string& a, const std::string& b)
{
    auto its = mismatch(makeRange(a), makeRange(b));
    if (its.first == begin(a))
        return std::string();
    if (its.first == end(a) && its.second == end(b))
    {
        if (!isDirSep(a.back()))
            return a;
    }
    else if (its.first == end(a) && isDirSep(*its.second) &&
             !isDirSep(a.back()))
    {
        return a;
    }
    else if (its.second == end(b) && isDirSep(*its.first) &&
             !isDirSep(b.back()))
    {
        return b;
    }
    auto it = find_last_if(makeRange(begin(a), its.first), isDirSep);
    if (it == begin(a) && isDirSep(*it))
        return DirSepStr;
    return std::string(begin(a), it);
}

std::string dirName(const std::string& path)
{
    auto p = makeRange(path);
    RawStrings::prevToken(p, isDirSep);
    if (empty(p) && !path.empty() && isDirSep(path[0]))
        return DirSepStr;
    return RawStrings::toString<char>(p);
}

std::string extension(const std::string& path)
{
    auto it = find_last_if(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isDirSep(*it) || isDirSep(*prev(it)))
        return std::string();
    return std::string(it, end(path));
}

bool isAbsPath(const std::string& path)
{
    if (path.empty())
        return false;
    return isDirSep(path[0]);
}

std::string join(std::string left, const std::string& right)
{
    if (left.empty())
        return right;
    if (right.empty())
        return left;

    bool sepL = isDirSep(left.back());
    bool sepR = isDirSep(right.front());
    if (sepL && sepR)
        return left.append(next(begin(right)), end(right));
    if (sepL || sepR)
        return left.append(right);
    return left.append(DirSepStr).append(right);
}

std::string normalize(const std::string& path)
{
    std::vector<std::string> result;
    auto parts = splitPath(path);
    for (auto it = begin(parts); it != end(parts); ++it)
    {
        if (*it == CurrentDir)
            continue;
        else if (*it != ParentDir)
            result.push_back(*it);
        else if (result.empty() || result.back() == ParentDir)
            result.push_back(*it);
        else if (!result.back().empty())
            result.pop_back();
    }
    if (result.empty())
        return CurrentDir;
    if (result.size() == 1 && result[0].empty())
        return DirSepStr;
    return RawStrings::join<std::string>(begin(result), end(result),
                                         DirSepStr);
}

std::string relativePath(const std::string& souce, const std::string& dest)
{
    auto normSource = normalize(souce);
    auto normDest = normalize(dest);
    auto common = commonPath(normSource, normDest);
    if (common.empty())
        return normDest;
    auto commonLength = common.size() + (common == DirSepStr ? 0 : 1);
    auto ascent = std::count_if(next(begin(normSource), commonLength),
                                end(normSource), isDirSep) + 1;
    std::string result;
    for (size_t i = 0; i != ascent; ++i)
        result.append("../");
    result.append(next(begin(normDest), commonLength), end(normDest));
    return result;
}

std::string removeExtension(const std::string& path)
{
    auto it = find_last_if(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isDirSep(*it) || isDirSep(*prev(it)))
        return path;
    return std::string(begin(path), it);
}

std::string replaceExtension(const std::string& path, const std::string& ext)
{
    return removeExtension(path) + ext;
}

std::pair<std::string, std::string> split(const std::string& path)
{
    auto p = makeRange(path);
    auto bn = RawStrings::prevToken(p, isDirSep);
    if (empty(p) && !path.empty() && isDirSep(path[0]))
        return std::make_pair(DirSepStr, RawStrings::toString<char>(bn));
    return std::make_pair(RawStrings::toString<char>(p),
                          RawStrings::toString<char>(bn));
}

std::pair<std::string, std::string> splitExtension(const std::string& path)
{
    auto it = find_last_if(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isDirSep(*it) || isDirSep(*prev(it)))
        return make_pair(path, std::string());
    return make_pair(std::string(begin(path), it),
                     std::string(it, end(path)));
}

std::vector<std::string> splitPath(const std::string& path)
{
    auto parts = RawStrings::splitIf(makeRange(path), isDirSep);
    std::vector<std::string> result;
    auto it = begin(parts);
    if (it == end(parts))
        return result;
    result.push_back(RawStrings::toString<char>(*it));
    for (++it; it != end(parts); ++it)
    {
        if (!empty(*it))
            result.push_back(RawStrings::toString<char>(*it));
    }
    return result;
}

}}}
