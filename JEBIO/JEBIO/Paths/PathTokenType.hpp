#ifndef JEBSTRING_PATHS_PATHTOKENTYPE_HPP
#define JEBSTRING_PATHS_PATHTOKENTYPE_HPP

#include "JEBIO/JEBIODefinitions.hpp"

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
