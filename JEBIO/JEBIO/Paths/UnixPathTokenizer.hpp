#ifndef JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP
#define JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP

#include "JEBBase/Ranges/Range.hpp"
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include "PathTokenType.hpp"

namespace JEBIO {

using JEBBase::Ranges::Range;
using JEBBase::Ranges::makeRange;

class UnixPathTokenizer
{
public:
    template <typename It>
    static std::pair<Range<It>, PathTokenType> next(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prev(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> nextSubToken(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prevSubToken(Range<It>& path);
};

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::next(Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = find(path, '/');
    if (it == path.end())
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != path.begin())
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DirSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prev(Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = findLast(path, '/');
    if (*it != '/')
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else
        return std::make_pair(takeTail(path, --it),
                              PathTokenType::DirSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::nextSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = findFirstOf(path, makeRange("/."));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (*it == '/')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DirSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::ExtensionSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prevSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = findLastOf(path, makeRange("/."));
    if (*it != '/' && *it != '.')
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (*--it == '/')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::DirSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::ExtensionSeparator);
}

}

#endif
