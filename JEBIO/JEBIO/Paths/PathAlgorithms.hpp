#ifndef JEBIO_PATHS_PATHS_HPP
#define JEBIO_PATHS_PATHS_HPP

#include <string>
#include <vector>
#include "JEBBase/Ranges/Range.hpp"
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

using JEBBase::Ranges::Range;

template <typename PathTokenizer, typename It>
Range<It> baseName(const PathTokenizer& tokenizer, Range<It> path);

template <typename PathTokenizer, typename It1, typename It2>
std::pair<Range<It1>, Range<It2>> commonPath(
        const PathTokenizer& tokenizer,
        Range<It1>& path1,
        Range<It2>& path2);

template <typename PathTokenizer, typename It1, typename It2>
std::pair<Range<It1>, Range<It2>> commonPath(
        const PathTokenizer& tokenizer,
        const Range<It1>& path1,
        const Range<It2>& path2);

template <typename PathTokenizer, typename It>
Range<It> dirName(const PathTokenizer& tokenizer, Range<It> path);

// /** @brief Returns the extension of path @a p, including the leading ".".
//   *
//   * If @a p doesn't have any extension, the function returns the
//   * empty string.
//   */
template <typename PathTokenizer, typename It>
Range<It> extension(const PathTokenizer& tokenizer, Range<It>& path);

template <typename PathTokenizer, typename It>
Range<It> extension(const PathTokenizer& tokenizer, const Range<It>& path);

// bool isAbsPath(const std::string& path);

// std::string join(std::string left, const std::string& right);

// std::string normalize(const std::string& path);

// std::string relativePath(const std::string& souce, const std::string& dest);

// std::string removeExtension(const std::string& path);

// std::string replaceExtension(const std::string& path, const std::string& ext);

// std::pair<std::string, std::string> split(const std::string& path);

// std::vector<std::string> splitPath(const std::string& path);

}

#include "PathAlgorithms.impl.hpp"

#endif
