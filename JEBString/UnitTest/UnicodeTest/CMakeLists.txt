cmake_minimum_required(VERSION 2.8)

project(UnicodeTest)

set(SRC
    test_CaseConverter.cpp
    test_CaseInsensitive.cpp
    test_CharClass.cpp
    test_CharMap.cpp
    test_CharMappingTypes.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
