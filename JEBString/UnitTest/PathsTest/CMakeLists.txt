cmake_minimum_required(VERSION 2.8)

project(PathsTest)

set(SRC
    test_PathFilter.cpp
    test_UnixPaths.cpp
    test_WindowsPaths.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
