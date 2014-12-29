cmake_minimum_required(VERSION 2.8)

project(JEBMath)

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
