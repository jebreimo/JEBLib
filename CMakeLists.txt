# JEBLib: a toolchest of functions and classes spanning a wide range
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBLib)

set(JEB_INSTALL_JEBLIB_API 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(
    ${CMAKE_SOURCE_DIR}/JEBBase
    ${CMAKE_SOURCE_DIR}/JEBMath
    ${CMAKE_SOURCE_DIR}/JEBString
    ${CMAKE_SOURCE_DIR}/JEBIO)

find_package(JEBDebug)
if(JEBDEBUG_FOUND)
    include_directories(${JEBDEBUG_INCLUDE_DIRS})
endif(JEBDEBUG_FOUND)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++ -Wall")
elseif(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(APPLE)

find_package(JEBTest)

set(JEB_INSTALL_JEBBASE_API 1)
add_subdirectory(JEBBase)

set(JEB_INSTALL_JEBMATH_API 1)
add_subdirectory(JEBMath)

set(JEB_INSTALL_JEBSTRING_API 1)
add_subdirectory(JEBString)

set(JEB_INSTALL_JEBIO_API 1)
add_subdirectory(JEBIO)

add_library(
    ${PROJECT_NAME} SHARED
            
    # JEBBase
    $<TARGET_OBJECTS:Bits>
    
    # JEBMath
    $<TARGET_OBJECTS:Geometry>
    $<TARGET_OBJECTS:Graphics>
    $<TARGET_OBJECTS:Math>

    # JEBString
    $<TARGET_OBJECTS:CodePageStrings>
    $<TARGET_OBJECTS:EncodedStrings>
    $<TARGET_OBJECTS:Encodings>
    $<TARGET_OBJECTS:Unicode>
    $<TARGET_OBJECTS:Utf8>
    $<TARGET_OBJECTS:Utf16>

    # JEBIO
    $<TARGET_OBJECTS:Json>
    $<TARGET_OBJECTS:Paths>
    $<TARGET_OBJECTS:Streams>
    $<TARGET_OBJECTS:Xml>
    )

set_property(TARGET ${PROJECT_NAME} PROPERTY MACOSX_RPATH ON)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
