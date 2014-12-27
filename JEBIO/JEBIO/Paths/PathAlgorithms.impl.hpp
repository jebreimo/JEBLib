#include "PathTokenType.hpp"

namespace JEBIO {

using JEBBase::Ranges::makeRange;

template <typename PathTokenizer, typename It>
Range<It> baseName(const PathTokenizer& tokenizer, Range<It> path)
{
    auto last = tokenizer.prev(path);
    if (last.second != PathTokenType::Name)
        return Range<It>();
    return last.first;
}

template <typename PathTokenizer, typename It1, typename It2>
std::pair<Range<It1>, Range<It2>> commonPath(
        const PathTokenizer& tokenizer,
        Range<It1>& path1,
        Range<It2>& path2)
{
    auto result1 = makeRange(begin(path1), begin(path1));
    auto result2 = makeRange(begin(path2), begin(path2));
    while (!empty(path1) && !empty(path2))
    {
        auto tok1 = tokenizer.next(path1);
        auto tok2 = tokenizer.next(path2);
        if (tok1.second != tok2.second || !equal(tok1.first, tok2.first))
        {
            path1.begin() = tok1.first.begin();
            path2.begin() = tok2.first.begin();
            break;
        }
        result1.end() = path1.begin();
        result2.end() = path2.begin();
    }
    return std::make_pair(result1, result2);
}

template <typename PathTokenizer, typename It1, typename It2>
std::pair<Range<It1>, Range<It2>> commonPath(
        const PathTokenizer& tokenizer,
        const Range<It1>& path1,
        const Range<It2>& path2)
{
    auto p1 = path1;
    auto p2 = path2;
    return commonPath(tokenizer, p1, p2);
}

template <typename PathTokenizer, typename It>
Range<It> dirName(const PathTokenizer& tokenizer, Range<It> path)
{
    auto tmp = path;
    auto last = tokenizer.prev(path);
    if (last.second == PathTokenType::Name)
    {
        tmp = path;
        last = tokenizer.prev(path);
    }
    if ((last.second == PathTokenType::DriveSeparator) ||
        (last.second == PathTokenType::DirSeparator && empty(path)))
        return tmp;
    return path;
}

template <typename PathTokenizer, typename It>
Range<It> extension(const PathTokenizer& tokenizer, Range<It>& path)
{
    auto tmp = path;
    auto last = tokenizer.prevSubToken(tmp);
    if (last.second != PathTokenType::ExtensionSeparator)
    {
        if (last.second != PathTokenType::Name)
            return Range<It>();
        last = tokenizer.prevSubToken(tmp);
        if (last.second != PathTokenType::ExtensionSeparator)
            return Range<It>();
    }
    auto result = makeRange(begin(last.first), end(path));
    auto pathEnd = end(tmp);
    last = tokenizer.prevSubToken(tmp);
    if (last.second != PathTokenType::Name)
        return Range<It>();
    path.end() = pathEnd;
    return result;
}

template <typename PathTokenizer, typename It>
Range<It> extension(const PathTokenizer& tokenizer, const Range<It>& path)
{
    auto tmp = path;
    return extension(tokenizer, tmp);
}

}
