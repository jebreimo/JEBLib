cmake_minimum_required(VERSION 2.8)

project(JsonTest)

set(SRC
    test_JsonTokenizer.cpp
    test_JsonValue.cpp
    test_JsonWriter.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
