cmake_minimum_required(VERSION 2.8)

project(XmlTest)

set(SRC
    test_XmlWriter.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
