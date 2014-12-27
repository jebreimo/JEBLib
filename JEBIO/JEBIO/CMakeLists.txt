cmake_minimum_required(VERSION 2.8)

project(JEBIO_Root)

set(JEB_DIR JEBIO)

add_subdirectory(Json)
add_subdirectory(Paths)
add_subdirectory(Streams)
add_subdirectory(Xml)

set(PUBLIC_HEADERS
    JEBMathDefinitions.hpp
    )

if (DEFINED JEB_INSTALL_JEBMATH_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBMATH_API)
