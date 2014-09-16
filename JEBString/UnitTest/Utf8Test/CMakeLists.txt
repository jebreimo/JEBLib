cmake_minimum_required(VERSION 2.8)

project(Utf8Test)

set(SRC
    test_Utf8String.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
