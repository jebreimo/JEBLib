# Try to find JEBTest
# Once done this will define
#  JEBTEST_FOUND - System has JEBTest
#  JEBTEST_INCLUDE_DIRS - The JEBTest include directories
#  JEBTEST_LIBRARIES - The libraries needed to use JEBTest
#  JEBTEST_DEFINITIONS - Compiler switches required for using JEBTest
find_path(JEBTEST_INCLUDE_DIR JEBTest/JEBTest.hpp
          PATH_SUFFIXES JEBTest)

find_library(JEBTEST_LIBRARY NAMES JEBTest libJEBTest)

set(JEBTEST_DEFINITIONS -std=c++11 -stdlib=libc++)

set(JEBTEST_LIBRARIES ${JEBTEST_LIBRARY})
set(JEBTEST_INCLUDE_DIRS ${JEBTEST_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

# Handle the QUIETLY and REQUIRED arguments and set JEBTEST_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(JEBTest DEFAULT_MSG
                                  JEBTEST_INCLUDE_DIR JEBTEST_LIBRARY)

mark_as_advanced(JEBTEST_INCLUDE_DIRS JEBTEST_LIBRARIES)
