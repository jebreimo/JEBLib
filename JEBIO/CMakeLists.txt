cmake_minimum_required(VERSION 2.8)

project(JEBIO)

set(JEB_INSTALL_JEBIO_API 1)

# include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
            ${JEB_SRC}
            $<TARGET_OBJECTS:Json>
            $<TARGET_OBJECTS:Paths>
            $<TARGET_OBJECTS:Streams>
            $<TARGET_OBJECTS:Xml>
            )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if(JEBTEST_FOUND)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(JEBTEST_FOUND)
