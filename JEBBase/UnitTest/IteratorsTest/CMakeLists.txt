# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(IteratorsTest)

set(SRC
    test_Iterators.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
