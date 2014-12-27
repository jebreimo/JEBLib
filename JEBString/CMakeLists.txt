cmake_minimum_required(VERSION 2.8)

project(JEBString)

set(JEB_INSTALL_JEBSTRING_API 1)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
#     "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
            ${JEB_SRC}
            $<TARGET_OBJECTS:CodePageStrings>
            $<TARGET_OBJECTS:EncodedStrings>
            $<TARGET_OBJECTS:Encodings>
            $<TARGET_OBJECTS:Unicode>
            $<TARGET_OBJECTS:Utf8>
            $<TARGET_OBJECTS:Utf16>
            )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if(JEBTEST_FOUND)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(JEBTEST_FOUND)
