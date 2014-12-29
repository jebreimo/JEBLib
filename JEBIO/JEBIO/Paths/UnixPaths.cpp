#include "UnixPaths.hpp"
#include <cstdint>
#include "JEBBase/Algorithms/Algorithms.hpp"
#include "JEBString/RawStrings/RawString.hpp"
#include "PathAlgorithms.hpp"
#include "UnixPathTokenizer.hpp"

namespace JEBIO { namespace Unix {

using JEBBase::Ranges::makeRange;
using JEBBase::Ranges::fromRange;

namespace
{
    const char DirSep = '/';
    static const std::string DirSepStr(1, DirSep);
    const char CurrentDir[] = ".";
    auto CurrentDirRange = makeRange(CurrentDir);
    const char ParentDir[] = "..";
    auto ParentDirRange = makeRange(ParentDir);

    bool isDirSep(uint32_t ch)
    {
        return ch == DirSep;
    }

    // bool isPathSep(uint32_t ch)
    // {
    //     return isDirSep(ch);
    // }

    bool isExtensionSep(uint32_t ch)
    {
        return ch == '.';
    }

    bool isDirOrExtensionSep(uint32_t ch)
    {
        return isDirSep(ch) || isExtensionSep(ch);
    }
}

std::string baseName(const std::string& path)
{
    return fromRange<std::string>(baseName(UnixPathTokenizer(),
                                           makeRange(path)));
}

std::string commonPath(const std::string& a, const std::string& b)
{
    return fromRange<std::string>(commonPath(UnixPathTokenizer(),
                                             makeRange(a),
                                             makeRange(b)).first);
}

std::string dirName(const std::string& path)
{
    return fromRange<std::string>(dirName(UnixPathTokenizer(),
                                          makeRange(path)));
}

std::string extension(const std::string& path)
{
    return fromRange<std::string>(extension(UnixPathTokenizer(),
                                            makeRange(path)));
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
    return JEBString::RawStrings::join<std::string>(
            begin(result), end(result), DirSepStr);
}

std::string relativePath(const std::string& souce, const std::string& dest)
{
    auto normSource = normalize(souce);
    auto normDest = normalize(dest);
    auto sourceRange = makeRange(normSource);
    auto destRange = makeRange(normDest);
    UnixPathTokenizer tokenizer;
    auto common = commonPath(tokenizer, sourceRange, destRange);
    if (empty(common.first))
        return normDest;

    std::string result;
    while (!empty(sourceRange))
    {
        if (tokenizer.next(sourceRange).second == PathTokenType::Name)
            result.append("../");
    }
    result.append(begin(destRange), end(destRange));
    return result;
}

std::string removeExtension(const std::string& path)
{
    auto pathRng = makeRange(path);
    extension(UnixPathTokenizer(), pathRng);
    return fromRange<std::string>(pathRng);
}

std::string replaceExtension(const std::string& path, const std::string& ext)
{
    if (!ext.empty() && ext[0] != '.')
        return removeExtension(path) + "." + ext;
    return removeExtension(path) + ext;
}

std::pair<std::string, std::string> split(const std::string& path)
{
    auto first = makeRange(path);
    auto second = makeRange(end(path), end(path));
    UnixPathTokenizer tokenizer;
    while (!empty(first))
    {
        auto token = tokenizer.prev(first);
        if (token.second == PathTokenType::DirSeparator)
        {
            if (empty(first))
                first = token.first;
            break;
        }
        second.begin() = token.first.begin();
    }
    return std::make_pair(fromRange<std::string>(first),
                          fromRange<std::string>(second));
}

std::pair<std::string, std::string> splitExtension(const std::string& path)
{
    auto it = findLastIf(makeRange(path), isDirOrExtensionSep);
    if (it == begin(path) || isDirSep(*it) || isDirSep(*prev(it)))
        return make_pair(path, std::string());
    return make_pair(std::string(begin(path), it),
                     std::string(it, end(path)));
}

std::vector<std::string> splitPath(const std::string& path)
{
    auto parts = JEBString::RawStrings::splitIf(makeRange(path), isDirSep);
    std::vector<std::string> result;
    auto it = begin(parts);
    if (it == end(parts))
        return result;
    result.push_back(JEBString::RawStrings::toString<char>(*it));
    for (++it; it != end(parts); ++it)
    {
        if (!empty(*it))
            result.push_back(JEBString::RawStrings::toString<char>(*it));
    }
    return result;
}

}}
