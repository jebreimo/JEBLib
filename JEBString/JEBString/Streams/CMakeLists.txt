cmake_minimum_required(VERSION 2.8)

project(Streams)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    StreamFill.hpp
    StreamJoin.hpp
    )

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
