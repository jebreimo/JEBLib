cmake_minimum_required(VERSION 2.8)

project(CodePageStrings)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    CodePageString.hpp
    CodePage.hpp
   )

set(SRC
    CodePageString.cpp
    CodePage.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
