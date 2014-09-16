cmake_minimum_required(VERSION 2.8)

project(Utf16)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Utf16String.hpp
    Utf16String_impl.hpp
    Utf16Utilities.hpp
   )

set(SRC
    Utf16String.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
