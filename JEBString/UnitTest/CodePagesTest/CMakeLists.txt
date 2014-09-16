cmake_minimum_required(VERSION 2.8)

project(CodePagesTest)

set(SRC
    test_Cp1252String.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
