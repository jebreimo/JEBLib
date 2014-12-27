#ifndef JEBSTRING_PATHS_PATHTOKENTYPE_HPP
#define JEBSTRING_PATHS_PATHTOKENTYPE_HPP

#include "JEBString/JEBStringDefinitions.hpp"

namespace JEBIO {

enum PathTokenType
{
    Empty,
    Name,
    DirSeparator,
    ExtensionSeparator,
    DriveSeparator
};

}

#endif
