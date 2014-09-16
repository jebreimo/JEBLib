cmake_minimum_required(VERSION 2.8)

project(Paths)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    PathFilter.hpp
    UnixPaths.hpp
    WindowsPaths.hpp
   )

set(SRC
    PathFilter.cpp
    UnixPaths.cpp
    WindowsPaths.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
