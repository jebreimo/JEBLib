# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(RangesTest)

set(SRC
    test_RangeAlgorithms.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
