# JEBString: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.

cmake_minimum_required(VERSION 2.8)

set(PARENT_PROJECT JEBIO)
project(${PARENT_PROJECT}Test)

set(SRC
    main.cpp
    )

add_subdirectory(JsonTest)
add_subdirectory(PathsTest)
add_subdirectory(StreamsTest)
add_subdirectory(XmlTest)

add_executable(${PROJECT_NAME}
               ${SRC}
               $<TARGET_OBJECTS:JsonTest>
               $<TARGET_OBJECTS:PathsTest>
               $<TARGET_OBJECTS:StreamsTest>
               $<TARGET_OBJECTS:XmlTest>
               )

target_link_libraries(${PROJECT_NAME}
                      JEBBase
                      JEBString
                      ${PARENT_PROJECT}
                      ${JEBTEST_LIBRARIES})
add_test(${PARENT_PROJECT} ${PROJECT_NAME})
