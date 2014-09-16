cmake_minimum_required(VERSION 2.8)

project(CodePointsTest)

set(SRC
    test_CodePointAlgorithms.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
