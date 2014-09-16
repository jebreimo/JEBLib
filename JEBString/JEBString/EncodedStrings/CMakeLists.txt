cmake_minimum_required(VERSION 2.8)

project(EncodedStrings)

set(JEB_DIR JEBString/${PROJECT_NAME})

set(PUBLIC_HEADERS
    CodePageEncoding.hpp
    DecodeUtf8.hpp
    DecodeUtf8_impl.hpp
    DecodeUtf16.hpp
    DecodeUtf16_impl.hpp
    EncodedRange.hpp
    EncodedString.hpp
    EncodedString_impl.hpp
    Encoder.hpp
    EncodeUtf8.hpp
    EncodeUtf8_impl.hpp
    EncodeUtf16.hpp
    EncodeUtf16_impl.hpp
    Encoding.hpp
    ForwardDecoder.hpp
    ReverseDecoder.hpp
    Utf8Encoding.hpp
    Utf16Encoding.hpp
   )

set(SRC
    EncodeUtf8.cpp
   )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBSTRING_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBSTRING_API)
