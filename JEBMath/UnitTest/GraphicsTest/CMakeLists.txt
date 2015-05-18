cmake_minimum_required(VERSION 2.8)

project(GraphicsTest)

set(SRC
    test_Color32.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
