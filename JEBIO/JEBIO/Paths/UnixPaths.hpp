#ifndef JEBIO_PATHS_UNIXPATHS_HPP
#define JEBIO_PATHS_UNIXPATHS_HPP

#include <string>
#include <vector>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO { namespace Unix {

std::string baseName(const std::string& path);

std::string commonPath(const std::string& a, const std::string& b);

std::string dirName(const std::string& path);

/** @brief Returns the extension of path @a p, including the leading ".".
  *
  * If @a p doesn't have any extension, the function returns the
  * empty string.
  */
std::string extension(const std::string& path);

bool isAbsPath(const std::string& path);

std::string join(std::string left, const std::string& right);

std::string normalize(const std::string& path);

std::string relativePath(const std::string& souce, const std::string& dest);

std::string removeExtension(const std::string& path);

std::string replaceExtension(const std::string& path, const std::string& ext);

std::pair<std::string, std::string> split(const std::string& path);

std::vector<std::string> splitDirs(const std::string& path);

std::pair<std::string, std::string> splitExtension(const std::string& path);

}}

#endif
