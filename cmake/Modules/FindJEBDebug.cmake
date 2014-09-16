# - Try to find JEBDebug
# Once done this will define
#  JEBDEBUG_FOUND - System has JEBDebug
#  JEBDEBUG_INCLUDE_DIRS - The JEBDebug include directories
#  JEBDEBUG_LIBRARIES - The libraries needed to use JEBDebug
#  JEBDEBUG_DEFINITIONS - Compiler switches required for using JEBDebug

find_path(JEBDEBUG_INCLUDE_DIR JEBDebug/Debug.hpp
          PATH_SUFFIXES JEBDebug)

set(JEBDEBUG_DEFINITIONS -std=c++11 -stdlib=libc++)
set(JEBDEBUG_LIBRARIES)
set(JEBDEBUG_INCLUDE_DIRS ${JEBDEBUG_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set JEBDEBUG_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(JEBDebug DEFAULT_MSG JEBDEBUG_INCLUDE_DIR)

mark_as_advanced(JEBDEBUG_INCLUDE_DIRS JEBDEBUG_LIBRARIES)
