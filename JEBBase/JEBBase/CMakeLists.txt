# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBBase_Root)

set(JEB_DIR JEBBase)

add_subdirectory(Algorithms)
add_subdirectory(Bits)
add_subdirectory(Containers)
add_subdirectory(Functional)
add_subdirectory(Iterators)
add_subdirectory(Ranges)
#add_subdirectory(StateMachine)

set(PUBLIC_HEADERS
    JEBBaseDefinitions.hpp
    JEBAlgorithms.hpp
    )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBBASE_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBBASE_API)
