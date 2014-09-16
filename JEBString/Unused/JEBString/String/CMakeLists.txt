cmake_minimum_required(VERSION 2.8)

project(String)

set(JEB_DIR JEB/${PROJECT_NAME})

set(PUBLIC_HEADERS
    FromString.hpp
    MapUtilities.hpp
    String.hpp
    StringConversion.hpp
    StringFlags.hpp
    StringPredicates.hpp
    ToString.hpp
    )

set(SRC
    FromString.cpp
    String.cpp
    StringConversion.cpp
    Generic/CharRangeSet.cpp
    Generic/WildCardMatcher.cpp
    Generic/WildCardWord.cpp
    Utf8/Encode.cpp
    )

set(PUBLIC_HEADERS_UTF8
    Utf8/Decode.hpp
    Utf8/Decode_Impl.hpp
    Utf8/Encode.hpp
    Utf8/Encode_Impl.hpp
    Utf8/EscapedString.hpp
    Utf8/EscapedFwdIt.hpp
    Utf8/Utf8Chars.hpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
    install(FILES ${PUBLIC_HEADERS_UTF8} DESTINATION include/${JEB_DIR}/Utf8)
endif(DEFINED JEB_INSTALL_JEBSTRING_API)

if (DEFINED JEB_INCLUDE_UNIT_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(DEFINED JEB_INCLUDE_UNIT_TESTS)
