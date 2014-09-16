cmake_minimum_required(VERSION 2.8)

project(StreamsTest)

set(SRC
    test_StreamFill.cpp
    test_StreamJoin.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
