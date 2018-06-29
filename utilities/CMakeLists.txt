
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message ( FATAL_ERROR "Prevented in-tree build." )
endif (  )

set ( CMAKE_LEGACY_CYGWIN_WIN32 OFF )

cmake_minimum_required ( VERSION 3.6.0 FATAL_ERROR )

project ( AVR_PROJECT VERSION 0.0.1.0 LANGUAGES C CXX )

add_executable ( parse parse.c )
add_executable ( bits bits.c )
add_executable ( serial_listen serial_listen.c )
add_executable ( tst-freq tst-freq.c )

target_link_libraries ( tst-freq PRIVATE -lm )

target_include_directories ( serial_listen PRIVATE ${CMAKE_SOURCE_DIR}/include )
