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
    auto DirSepRange = makeRange(DirSepStr);
    const char CurrentDir[] = ".";
    auto CurrentDirRange = makeRange(CurrentDir);
    const char ParentDir[] = "..";
    auto ParentDirRange = makeRange(ParentDir);

    bool isDirSep(uint32_t ch)
    {
        return ch == DirSep;
    }

    template <typename Iterator>
    bool endsWithDirSep(Range<Iterator> str)
    {
        return !empty(str) && isDirSep(back(str));
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

template <typename Iterator>
void append(std::string& left, Range<Iterator> right)
{
    if (empty(right))
        return;

    if (left.empty())
    {
        left.assign(begin(right), end(right));
        return;
    }

    bool sepL = isDirSep(left.back());
    bool sepR = isDirSep(back(right));
    if (sepL && sepR)
        left.append(next(begin(right)), end(right));
    else if (sepL || sepR)
        left.append(begin(right), end(right));
    else
        left.append(DirSepStr).append(begin(right), end(right));
}

std::string normalize(const std::string& path)
{
    typedef Range<std::string::const_iterator> StrRange;

    std::vector<StrRange> dirs;

    UnixPathTokenizer tokenizer;
    auto pathRng = makeRange(path);
    auto dir = splitFront(tokenizer, pathRng);
    while (!empty(dir))
    {
        if (equal(dir, ParentDirRange))
        {
            if (dirs.empty() || equal(dirs.back(), ParentDirRange))
                dirs.push_back(dir);
            else if (!endsWithDirSep(dirs.back()))
                dirs.pop_back();
        }
        else if (!equal(dir, CurrentDirRange) &&
                 (dirs.empty() || !equal(dir, DirSepRange)))
        {
            dirs.push_back(dir);
        }
        dir = splitFront(tokenizer, pathRng);
    }
    if (equal(pathRng, ParentDirRange))
    {
        if (dirs.empty() || equal(dirs.back(), ParentDirRange))
            dirs.push_back(pathRng);
        else if (!endsWithDirSep(dirs.back()))
            dirs.pop_back();
    }
    else if (!equal(pathRng, CurrentDirRange) &&
             (dirs.empty() || !equal(pathRng, DirSepRange)))
    {
        dirs.push_back(pathRng);
    }

    std::string result;
    for (auto it = begin(dirs); it != end(dirs); ++it)
        append(result, *it);

    if (result.empty())
        result = CurrentDir;
    return result;
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
    auto second = splitBack(UnixPathTokenizer(), first);
    return std::make_pair(fromRange<std::string>(first),
                          fromRange<std::string>(second));
}

std::vector<std::string> splitDirs(const std::string& path)
{
    std::vector<std::string> result;

    UnixPathTokenizer tokenizer;
    auto pathRng = makeRange(path);
    auto dir = splitFront(tokenizer, pathRng);
    while (!empty(dir))
    {
        result.push_back(fromRange<std::string>(dir));
        dir = splitFront(tokenizer, pathRng);
    }
    result.push_back(fromRange<std::string>(pathRng));
    return result;
}

std::pair<std::string, std::string> splitExtension(const std::string& path)
{
    auto first = makeRange(path);
    auto second = extension(UnixPathTokenizer(), first);
    return std::make_pair(fromRange<std::string>(first),
                          fromRange<std::string>(second));
}

}}
