# JEBBase: generic algorithms and functions
# Copyright 2014 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(Bits)

set(JEB_DIR JEBBase/${PROJECT_NAME})

set(PUBLIC_HEADERS
    BitIterator.hpp
    Bits.hpp
    Bits_Impl.hpp
    BitSet.hpp
    Endian.hpp
    Integers.hpp
    PackedDateTime.hpp
    SparseBitSet.hpp
    Union16.hpp
    Union32.hpp
    Union64.hpp
    )

set(SRC
    BitSet.cpp
    PackedDateTime.cpp
    SparseBitSet.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBBASE_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBBASE_API)
