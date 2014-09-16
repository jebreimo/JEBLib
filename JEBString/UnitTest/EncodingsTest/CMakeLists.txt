cmake_minimum_required(VERSION 2.8)

project(EncodingsTest)

set(SRC
    test_Encoding.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
