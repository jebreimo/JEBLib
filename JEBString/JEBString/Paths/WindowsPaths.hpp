#ifndef JEBSTRING_PATHS_WINDOWSPATHS_HPP
#define JEBSTRING_PATHS_WINDOWSPATHS_HPP

#include <string>
#include <vector>
#include "JEBString/JEBStringDefinitions.hpp"

namespace JEBString { namespace Paths { namespace Windows {

std::string extension(const std::string& p);

std::string removeExtension(const std::string& p);

std::pair<std::string, std::string> split(const std::string& path);

std::pair<std::string, std::string> splitExtension(const std::string& p);

}}}

#endif
