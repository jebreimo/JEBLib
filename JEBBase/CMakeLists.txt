# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBBase)

set(JEB_INSTALL_JEBMATH_API 1)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
            ${JEB_SRC}
            $<TARGET_OBJECTS:Bits>
           )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if(JEBTEST_FOUND)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(JEBTEST_FOUND)
