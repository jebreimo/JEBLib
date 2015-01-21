cmake_minimum_required(VERSION 2.8)

project(JEBMath_Root)

set(JEB_DIR JEBMath)

add_subdirectory(Geometry)
add_subdirectory(Graphics)
add_subdirectory(Math)

set(PUBLIC_HEADERS
    JEBMathDefinitions.hpp
    JEBVectorMath.hpp
    )

if (DEFINED JEB_INSTALL_JEBMATH_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBMATH_API)
