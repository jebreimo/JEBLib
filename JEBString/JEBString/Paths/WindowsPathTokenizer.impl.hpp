#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBString { namespace Paths {

using JEBBase::Ranges::makeRange;

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::next(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_first_of(path, makeRange("\\:"));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (*it == '\\')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathDriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prev(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_last_of(path, makeRange("\\:"));
    if (*it != '\\' && *it != ':')
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (*--it == '\\')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathDriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::nextSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_first_of(path, makeRange("\\:."));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::PathName);
    else if (*it == '\\')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathSeparator);
    else if (*it == ':')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathDriveSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::PathExtensionSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prevSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::EmptyPath);

    auto it = find_last_of(path, makeRange("\\:."));
    if (*it != '\\' && *it != ':' && *it != '.')
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::PathName);
    else if (*--it == '\\')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathSeparator);
    else if (*it == ':')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathDriveSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::PathExtensionSeparator);
}

}}
