cmake_minimum_required(VERSION 2.8)

project(Streams)

set(JEB_DIR JEBIO/${PROJECT_NAME})

set(PUBLIC_HEADERS
    StreamFill.hpp
    StreamJoin.hpp
    StreamRedirection.hpp
    )

set(SRC
    StreamRedirection.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
