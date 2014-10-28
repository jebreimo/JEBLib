#ifndef JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP
#define JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP

#include "JEBBase/Ranges/Range.hpp"
#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBString { namespace Paths {

using JEBBase::Ranges::Range;
using JEBBase::Ranges::makeRange;

enum PathTokenType
{
    EmptyPath,
    PathName,
    PathSeparator,
    PathExtensionSeparator
};

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
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find(path, '/');
    if (it == path.end())
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (it != path.begin())
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prev(Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_last(path, '/');
    if (*it != '/')
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else
        return std::make_pair(takeTail(path, --it),
                              PathTokenType::PathSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::nextSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_first_of(path, makeRange("/."));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (*it == '/')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathExtensionSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prevSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_last_of(path, makeRange("/."));
    if (*it != '/' && *it != '.')
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (*--it == '/')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathExtensionSeparator);
}

}}

#endif
