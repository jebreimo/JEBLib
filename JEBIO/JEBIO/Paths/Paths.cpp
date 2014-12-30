#include "Paths.hpp"

#ifdef WIN32
    #include "WindowsPaths.hpp"
    #define PATHS_IMPL_NS Windows
#else
    #include "UnixPaths.hpp"
    #define PATHS_IMPL_NS Unix
#endif

namespace JEBIO {

std::string baseName(const std::string& path)
{
    return PATHS_IMPL_NS::baseName(path);
}

std::string extension(const std::string& path)
{
    return PATHS_IMPL_NS::extension(path);
}

std::string removeExtension(const std::string& path)
{
    return PATHS_IMPL_NS::removeExtension(path);
}

std::pair<std::string, std::string> split(const std::string& path)
{
    return PATHS_IMPL_NS::split(path);
}

std::pair<std::string, std::string> splitExtension(const std::string& path)
{
    return PATHS_IMPL_NS::splitExtension(path);
}

std::vector<std::string> splitPath(const std::string& path)
{
    return PATHS_IMPL_NS::splitPath(path);
}

}
