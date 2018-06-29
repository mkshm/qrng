
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message ( FATAL_ERROR "Prevented in-tree build." )
endif (  )

set ( CMAKE_LEGACY_CYGWIN_WIN32 OFF )

cmake_minimum_required ( VERSION 3.6.0 FATAL_ERROR )

project ( AVR_PROJECT VERSION 0.0.1.0 LANGUAGES C CXX )

link_libraries ( -lm )
include_directories ( ${CMAKE_SOURCE_DIR} )

add_executable ( tst-freq tst-freq.c )
add_executable ( tst-monte-3d tst-monte-3d.c )