# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

set(PARENT_PROJECT JEBMath)
project(${PARENT_PROJECT}Test)

include_directories(${JEBTEST_INCLUDE_DIRS})

set(SRC
    main.cpp
    )

add_subdirectory(GeometryTest)
add_subdirectory(GraphicsTest)
add_subdirectory(MathTest)

add_executable(${PROJECT_NAME}
               ${SRC}
               $<TARGET_OBJECTS:GeometryTest>
               $<TARGET_OBJECTS:GraphicsTest>
               $<TARGET_OBJECTS:MathTest>
               )

target_link_libraries(${PROJECT_NAME}
                      JEBBase
                      ${PARENT_PROJECT}
                      ${JEBTEST_LIBRARIES})
add_test(${PARENT_PROJECT} ${PROJECT_NAME})
