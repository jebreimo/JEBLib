cmake_minimum_required(VERSION 2.8)

project(Paths)

set(JEB_DIR JEBIO/${PROJECT_NAME})

set(PUBLIC_HEADERS
    PathFilter.hpp
    PathTokenType.hpp
    PathAlgorithms.hpp
    PathAlgorithms.impl.hpp
    Paths.hpp
    UnixPaths.hpp
    UnixPathTokenizer.hpp
    WindowsPaths.hpp
    WindowsPathTokenizer.hpp
    WindowsPathTokenizer.impl.hpp
   )

set(SRC
    PathFilter.cpp
    Paths.cpp
    UnixPaths.cpp
    WindowsPaths.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBIO_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBIO_API)
