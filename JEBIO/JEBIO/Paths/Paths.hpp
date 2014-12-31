#ifndef JEBIO_PATHS_PATHS_HPP
#define JEBIO_PATHS_PATHS_HPP

#include <string>
#include <vector>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

std::string baseName(const std::string& path);

/** @brief Returns the extension of path @a p, including the leading ".".
  *
  * If @a p doesn't have any extension, the function returns the
  * empty string.
  */
std::string extension(const std::string& path);

std::string removeExtension(const std::string& path);

std::pair<std::string, std::string> split(const std::string& path);

std::vector<std::string> splitDirs(const std::string& path);

std::pair<std::string, std::string> splitExtension(const std::string& path);

}

#endif
