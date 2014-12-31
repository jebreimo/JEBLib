#include "WindowsPaths.hpp"
#include <cstdint>
#include "JEBBase/Iterators/Iterators.hpp"
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include "JEBString/RawStrings/RawString.hpp"
#include "PathAlgorithms.hpp"
#include "WindowsPathTokenizer.hpp"

namespace JEBIO { namespace Windows {

using JEBBase::Ranges::fromRange;
using JEBBase::Ranges::makeRange;
using namespace JEBString;

namespace
{
    static const std::string DirSepStr("\\");
}

std::string baseName(const std::string& path)
{
    return fromRange<std::string>(baseName(WindowsPathTokenizer(),
                                           makeRange(path)));
}

std::string dirName(const std::string& path)
{
    return fromRange<std::string>(dirName(WindowsPathTokenizer(),
                                          makeRange(path)));
}

std::string extension(const std::string& path)
{
    return fromRange<std::string>(extension(WindowsPathTokenizer(),
                                            makeRange(path)));
}

std::string removeExtension(const std::string& path)
{
    auto pathRng = makeRange(path);
    extension(WindowsPathTokenizer(), pathRng);
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
    auto second = splitBack(WindowsPathTokenizer(), first);
    return std::make_pair(fromRange<std::string>(first),
                          fromRange<std::string>(second));
}

std::vector<std::string> splitDirs(const std::string& path)
{
    std::vector<std::string> result;

    WindowsPathTokenizer tokenizer;
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
    auto second = extension(WindowsPathTokenizer(), first);
    return std::make_pair(fromRange<std::string>(first),
                          fromRange<std::string>(second));
}

}}
