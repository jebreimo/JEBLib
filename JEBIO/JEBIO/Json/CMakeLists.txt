cmake_minimum_required(VERSION 2.8)

project(Json)

set(JEB_DIR JEBIO/${PROJECT_NAME})

set(PUBLIC_HEADERS
    JsonTokenizer.hpp
    JsonValue.hpp
    JsonValueError.hpp
    JsonWriter.hpp
    )

set(SRC
    JsonTokenizer.cpp
    JsonValue.cpp
    JsonWriter.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBIO_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBIO_API)
