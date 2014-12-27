#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBIO {

using JEBBase::Ranges::makeRange;

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::next(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = find_first_of(path, makeRange("\\:"));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (*it == '\\')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DirSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prev(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = find_last_of(path, makeRange("\\:"));
    if (*it != '\\' && *it != ':')
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (*--it == '\\')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::DirSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::DriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::nextSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = find_first_of(path, makeRange("\\:."));
    if (it == end(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != begin(path))
        return std::make_pair(takeHead(path, it), PathTokenType::Name);
    else if (*it == '\\')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DirSeparator);
    else if (*it == ':')
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::DriveSeparator);
    else
        return std::make_pair(takeHead(path, ++it),
                              PathTokenType::ExtensionSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prevSubToken(
        Range<It>& path)
{
    if (empty(path))
        return std::make_pair(path, PathTokenType::Empty);

    auto it = find_last_of(path, makeRange("\\:."));
    if (*it != '\\' && *it != ':' && *it != '.')
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return std::make_pair(takeTail(path, it), PathTokenType::Name);
    else if (*--it == '\\')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::DirSeparator);
    else if (*it == ':')
        return std::make_pair(takeTail(path, it),
                              PathTokenType::DriveSeparator);
    else
        return std::make_pair(takeTail(path, it),
                              PathTokenType::ExtensionSeparator);
}

}
