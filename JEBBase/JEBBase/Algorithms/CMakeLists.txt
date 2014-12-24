# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(Algorithms)

set(JEB_DIR JEBBase/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Algorithms.hpp
    AlgorithmsCpp14.hpp
    KeyFunctionAlgorithms.hpp
    Sort.hpp
    )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBBASE_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBBASE_API)
