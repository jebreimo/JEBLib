cmake_minimum_required(VERSION 2.8)

project(JEBMath)

# set(JEB_INSTALL_JEBMATH_API 1)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
#     "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# include_directories(${CMAKE_SOURCE_DIR})

# if(APPLE)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wall")
# elseif(WIN32)
#     add_definitions(-D_SCL_SECURE_NO_WARNINGS)
# endif(APPLE)

add_subdirectory(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
            ${JEB_SRC}
            $<TARGET_OBJECTS:Geometry>
            $<TARGET_OBJECTS:Graphics>
            $<TARGET_OBJECTS:Math>
            )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if(JEBTEST_FOUND)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(JEBTEST_FOUND)
