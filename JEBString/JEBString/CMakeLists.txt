cmake_minimum_required(VERSION 2.8)

project(JEBString_Root)

set(JEB_DIR JEBString)

add_subdirectory(CodePageStrings)
add_subdirectory(CodePoints)
add_subdirectory(EncodedStrings)
add_subdirectory(Encodings)
add_subdirectory(RawStrings)
add_subdirectory(Unicode)
add_subdirectory(Utf16)
add_subdirectory(Utf8)

set(PUBLIC_HEADERS
    JEBStringDefinitions.hpp
    JEBStringFlags.hpp
    JEBStringMacros.hpp
    JEBUtf16.hpp
    JEBUtf8.hpp
   )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
