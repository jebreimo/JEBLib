cmake_minimum_required(VERSION 2.8)

project(JsonTest)

set(SRC
    testsuite_JsonTokenizer.cpp
    testsuite_JsonValue.cpp
    testsuite_JsonWriter.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
