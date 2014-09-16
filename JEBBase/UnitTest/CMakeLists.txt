# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBBaseTest)

include_directories(${JEBTEST_INCLUDE_DIRS})

set(SRC
    main.cpp
    )

add_subdirectory(AlgorithmsTest)
add_subdirectory(BitsTest)
add_subdirectory(ContainersTest)
add_subdirectory(IteratorsTest)
add_subdirectory(RangesTest)
add_subdirectory(StateMachineTest)

add_executable(${PROJECT_NAME}
               ${SRC}
               $<TARGET_OBJECTS:AlgorithmsTest>
               $<TARGET_OBJECTS:BitsTest>
               $<TARGET_OBJECTS:ContainersTest>
               $<TARGET_OBJECTS:IteratorsTest>
               $<TARGET_OBJECTS:RangesTest>
               $<TARGET_OBJECTS:StateMachineTest>
               )

target_link_libraries(${PROJECT_NAME} JEBBase ${JEBTEST_LIBRARIES})
add_test(JEBBase ${PROJECT_NAME})
