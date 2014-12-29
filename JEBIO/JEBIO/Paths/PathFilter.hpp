#ifndef JEBSTRING_PATHS_PATHFILTER_HPP
#define JEBSTRING_PATHS_PATHFILTER_HPP

#include <string>
#include <vector>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

enum PathFilterType
{
    ExclusiveFilter,
    InclusiveFilter
};

class FilterState;

class PathFilter
{
public:
    PathFilter();
    ~PathFilter();

    bool descend(const std::string& name);
    bool shouldDescend(const std::string& name);
    bool ascend();

    void excludePath(const std::string& path);
    void includePath(const std::string& path);

    PathFilterType type() const;
    void setType(PathFilterType type);
private:
    std::vector<FilterState> m_States;
};

}

#endif
