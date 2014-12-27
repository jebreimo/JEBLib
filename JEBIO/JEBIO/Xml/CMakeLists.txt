cmake_minimum_required(VERSION 2.8)

project(Xml)

set(JEB_DIR JEBIO/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Indentation.hpp
    XmlWriter.hpp
    )

set(SRC
    Indentation.cpp
    XmlWriter.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBIO_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBIO_API)
