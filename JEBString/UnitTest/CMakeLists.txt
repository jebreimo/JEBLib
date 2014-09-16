# JEBString: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.

cmake_minimum_required(VERSION 2.8)

set(PARENT_PROJECT JEBString)
project(${PARENT_PROJECT}Test)

set(SRC
    main.cpp
    )

add_subdirectory(CodePagesTest)
add_subdirectory(CodePointsTest)
add_subdirectory(EncodedStringsTest)
add_subdirectory(EncodingsTest)
add_subdirectory(UnicodeTest)
add_subdirectory(PathsTest)
add_subdirectory(StreamsTest)
add_subdirectory(Utf8Test)
add_subdirectory(Utf16Test)

add_executable(${PROJECT_NAME}
               ${SRC}
               $<TARGET_OBJECTS:CodePagesTest>
               $<TARGET_OBJECTS:CodePointsTest>
               $<TARGET_OBJECTS:EncodedStringsTest>
               $<TARGET_OBJECTS:EncodingsTest>
               $<TARGET_OBJECTS:PathsTest>
               $<TARGET_OBJECTS:StreamsTest>
               $<TARGET_OBJECTS:UnicodeTest>
               $<TARGET_OBJECTS:Utf8Test>
               $<TARGET_OBJECTS:Utf16Test>
               )

target_link_libraries(${PROJECT_NAME}
                      JEBBase
                      ${PARENT_PROJECT}
                      ${JEBTEST_LIBRARIES})
add_test(JEBString ${PROJECT_NAME})
