cmake_minimum_required(VERSION 2.8)

project(CodePoints)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    CodePointAlgorithms.hpp
    CodePointIterator.hpp
    CodePointString.hpp
    CodePointString_impl.hpp
   )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
