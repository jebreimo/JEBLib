cmake_minimum_required(VERSION 2.8)

project(EncodedStringsTest)

set(SRC
    test_Utf8.cpp
    test_Utf16.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
