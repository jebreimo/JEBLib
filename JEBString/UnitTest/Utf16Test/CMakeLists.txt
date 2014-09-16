cmake_minimum_required(VERSION 2.8)

project(Utf16Test)

set(SRC
    test_Utf16String.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
