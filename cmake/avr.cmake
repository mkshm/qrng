
set ( AVR_CFLAGS "-ffunction-sections -fdata-sections" CACHE STRING "AVR compilation flags" )
set ( AVR_LFLAGS "-Wl,--relax,--gc-sections" CACHE STRING "AVR link flags" )

find_program ( AVR_GCC     avr-gcc     )
find_program ( AVR_GXX     avr-g++     )
find_program ( AVR_RANLIB  avr-ranlib  )
find_program ( AVR_AR      avr-ar      )
find_program ( AVR_NM      avr-nm      )
find_program ( AVR_GDB     avr-gdb     )
find_program ( AVR_SIZE    avr-size    )
find_program ( AVR_STRIP   avr-strip   )
find_program ( AVR_OBJCOPY avr-objcopy )
find_program ( AVR_OBJDUMP avr-objdump )
find_program ( AVRDUDE     avrdude     )
find_program ( SIMAVR      simavr      )

set ( CMAKE_SYSTEM_NAME  Generic )
set ( CMAKE_AR           ${AVR_AR}     )
set ( CMAKE_RANLIB       ${AVR_RANLIB} )
set ( CMAKE_C_COMPILER   ${AVR_GCC}    )
set ( CMAKE_CXX_COMPILER ${AVR_GXX}    )

if ( NOT CMAKE_BUILD_TYPE )
  set ( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif ( NOT CMAKE_BUILD_TYPE )

function ( avr_add_executable EXECUTABLE )
  if ( NOT AVR_MCU OR NOT AVR_MCU_FREQ )
    message ( FATAL_ERROR "AVR_MCU or AVR_MCU_FREQ not defined" )
  endif (  )

  set ( EXECUTABLE_ELF "${EXECUTABLE}.elf" )
  set ( EXECUTABLE_HEX "${EXECUTABLE}.hex" )
  set ( EXECUTABLE_EEP "${EXECUTABLE}.eep" )

  add_custom_target ( ${EXECUTABLE} ALL
    DEPENDS ${EXECUTABLE_HEX} ${EXECUTABLE_EEP}
  )

  add_executable ( ${EXECUTABLE_ELF} ${ARGN} )

  set_target_properties ( ${EXECUTABLE_ELF} PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_MCU_FREQ} ${AVR_CFLAGS}"
    LINK_FLAGS    "-mmcu=${AVR_MCU} ${AVR_LFLAGS}"
  )

  add_custom_command ( OUTPUT ${EXECUTABLE_HEX}
    COMMAND ${AVR_OBJCOPY} -j .text -j .data -O ihex ${EXECUTABLE_ELF} ${EXECUTABLE_HEX}
    DEPENDS ${EXECUTABLE_ELF}
  )

  add_custom_command ( OUTPUT ${EXECUTABLE_EEP}
    COMMAND ${AVR_OBJCOPY} -j .eeprom --change-section-lma .eeprom=0 -O ihex ${EXECUTABLE_ELF} ${EXECUTABLE_EEP}
    DEPENDS ${EXECUTABLE_ELF}
  )

  add_custom_command ( TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${AVR_SIZE} -C --mcu=${AVR_MCU} ${EXECUTABLE_ELF}
  )
endfunction ( avr_add_executable EXECUTABLE )

function ( avr_add_library LIBRARY )
  if ( NOT AVR_MCU OR NOT AVR_MCU_FREQ )
    message ( FATAL_ERROR "AVR_MCU or AVR_MCU_FREQ not defined" )
  endif (  )
  add_library ( ${LIBRARY} ${ARGN} )
  set_target_properties ( ${LIBRARY} PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_MCU_FREQ} ${AVR_CFLAGS}"
    LINK_FLAGS    "-mmcu=${AVR_MCU} ${AVR_LFLAGS}"
  )
endfunction ( avr_add_library LIBRARY )

function ( avr_target_link_libraries TARGET )
  target_link_libraries ( ${TARGET}.elf ${ARGN} )
endfunction ( avr_target_link_libraries TARGET )

function ( avr_upload EXECUTABLE )
if ( AVR_PROGRAM_EEPROM )
  add_custom_target ( upload_$EXECUTABLE
    COMMAND ${AVRDUDE} -p ${AVR_MCU} -c ${AVR_PROGRAMMER} -b ${AVR_PROGRAMMER_BAUD} -P ${AVR_PROGRAMMER_PORT} -U flash:w:${EXECUTABLE}.hex -U eeprom:w:${EXECUTABLE}.eep
  )
else ( AVR_PROGRAM_EEPROM )
  add_custom_target ( upload_$EXECUTABLE
    COMMAND ${AVRDUDE} -p ${AVR_MCU} -c ${AVR_PROGRAMMER} -b ${AVR_PROGRAMMER_BAUD} -P ${AVR_PROGRAMMER_PORT} -U flash:w:${EXECUTABLE}.hex
  )
endif ( AVR_PROGRAM_EEPROM )
endfunction ( avr_upload EXECUTABLE )
