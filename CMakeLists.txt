
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message ( FATAL_ERROR "Prevented in-tree build." )
endif (  )

set ( CMAKE_LEGACY_CYGWIN_WIN32 OFF )

cmake_minimum_required ( VERSION 3.10.0 FATAL_ERROR )

set ( CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr.cmake" )
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

project ( AVR_PROJECT VERSION 0.0.1.0 LANGUAGES C CXX )

set ( AVR_MCU atmega328p )
set ( AVR_MCU_FREQ 16000000UL )
set ( AVR_PROGRAMMER arduino )
set ( AVR_PROGRAMMER_PORT /dev/ttyACM0 )
set ( AVR_PROGRAMMER_BAUD 19200 )
set ( AVR_PROGRAM_EEPROM FALSE )

set ( CMAKE_C_FLAGS "-I ${CMAKE_SOURCE_DIR}/include -I /usr/include/simavr" )

avr_add_executable ( qrng qrng.c )
avr_add_executable ( laser laser.c )
