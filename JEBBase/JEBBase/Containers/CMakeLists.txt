# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(Containers)

set(JEB_DIR JEBBase/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Array2D.hpp
    Array2D_Impl.hpp
    Buffer2D.hpp
    Buffer2D_Impl.hpp
    IntervalMap.hpp
    MapUtilities.hpp
    PairUtilities.hpp
    SetUtilities.hpp
    UniquePairSet.hpp
    VectorUtilities.hpp
    )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBBASE_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBBASE_API)
