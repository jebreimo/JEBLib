cmake_minimum_required(VERSION 2.8)

project(JEBCommonTest)

set(SRC
    main.cpp
    testsuite_Base64.cpp
    testsuite_Integers.cpp
    )

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} JEBLib JEBTest)
add_test(JEBLib ${PROJECT_NAME})
