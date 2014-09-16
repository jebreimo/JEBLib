cmake_minimum_required(VERSION 2.8)

project(JEBStringTest)

set(SRC
    main.cpp
    testsuite_CharRangeSet.cpp
    testsuite_Finder.cpp
    testsuite_Predicates.cpp
    testsuite_Replace.cpp
    testsuite_Split.cpp
    testsuite_SplitIterator.cpp
    testsuite_String.cpp
    testsuite_StringConversion.cpp
    testsuite_TokenIterator.cpp
    testsuite_Utf8.cpp
    testsuite_Utf8BiIterator.cpp
    testsuite_Utf8EscapedString.cpp
    testsuite_Utf8FwdIterator.cpp
    testsuite_Utf8OutIterator.cpp
    testsuite_Utf16.cpp
    testsuite_Utf16BiIterator.cpp
    testsuite_Wildcards.cpp
    )

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} JEBLib JEBTest)
add_test(JEBLib ${PROJECT_NAME})
