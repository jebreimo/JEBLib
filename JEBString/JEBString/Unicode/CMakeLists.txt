cmake_minimum_required(VERSION 2.8)

project(Unicode)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    CaseConverter.hpp
    CaseInsensitive.hpp
    CharClass.hpp
    CharMap.hpp
    CharMappingTypes.hpp
    StandardLowerCase.hpp
    StandardTitleCase.hpp
    StandardUpperCase.hpp
    UnicodeChars.hpp
    UnicodePredicates.hpp
    )

set(SRC
    CaseConverter.cpp
    CharClass.cpp
    CharMap.cpp
    CharMappingTypes.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
