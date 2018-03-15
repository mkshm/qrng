
set ( AVR_CFLAGS "-ffunction-sections -fdata-sections" CACHE STRING "AVR compilation flags" )
set ( AVR_LFLAGS "-Wl,--relax,--gc-sections -Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000" CACHE STRING "AVR link flags" )

find_program ( AVR_GCC        avr-gcc         )
find_program ( AVR_GXX        avr-g++         )
find_program ( AVR_RANLIB     avr-ranlib      )
find_program ( AVR_GCC_RANLIB avr-gcc-ranlib  )
find_program ( AVR_AR         avr-ar          )
find_program ( AVR_GCC_AR     avr-gcc-ar      )
find_program ( AVR_NM         avr-nm          )
find_program ( AVR_LD         avr-ld          )
find_program ( AVR_GDB        avr-gdb         )
find_program ( AVR_SIZE       avr-size        )
find_program ( AVR_STRIP      avr-strip       )
find_program ( AVR_OBJCOPY    avr-objcopy     )
find_program ( AVR_OBJDUMP    avr-objdump     )
find_program ( AVR_AVRDUDE    avrdude         )
find_program ( AVR_SIMAVR     simavr          )

set ( CMAKE_SYSTEM_NAME      Generic )
set ( CMAKE_SYSTEM_PROCESSOR avr     )
set ( CMAKE_CROSSCOMPILING   TRUE    )

set ( CMAKE_AR                  ${AVR_AR}         )
set ( CMAKE_CXX_COMPILER_AR     ${AVR_GCC_AR}     )
set ( CMAKE_C_COMPILER_AR       ${AVR_GCC_AR}     )
set ( CMAKE_NM                  ${AVR_NM}         )
set ( CMAKE_LINKER              ${AVR_LD}         )
set ( CMAKE_STRIP               ${AVR_STRIP}      )
set ( CMAKE_RANLIB              ${AVR_RANLIB}     )
set ( CMAKE_CXX_COMPILER_RANLIB ${AVR_GCC_RANLIB} )
set ( CMAKE_C_COMPILER_RANLIB   ${AVR_GCC_RANLIB} )
set ( CMAKE_OBJCOPY             ${AVR_OBJCOPY}    )
set ( CMAKE_OBJDUMP             ${AVR_OBJDUMP}    )
set ( CMAKE_C_COMPILER          ${AVR_GCC}        )
set ( CMAKE_CXX_COMPILER        ${AVR_GXX}        )

set ( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set ( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY  )
set ( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY  )

if ( NOT CMAKE_BUILD_TYPE )
  set ( CMAKE_BUILD_TYPE MinSizeRel CACHE STRING "Choose the type of build." FORCE )
endif ( NOT CMAKE_BUILD_TYPE )

function ( avr_add_executable AVR_TARGET )
  cmake_parse_arguments ( PARSE_ARGV 1 AVR "" "" "PROPERTIES" )
  set ( AVR_SOURCES ${AVR_UNPARSED_ARGUMENTS} )
  cmake_parse_arguments ( AVR "" "MCU;MCU_FREQ" "" ${AVR_PROPERTIES} )

  define_property ( TARGET PROPERTY AVR_MCU      BRIEF_DOCS "DEBUG" FULL_DOCS "DEBUG" )
  define_property ( TARGET PROPERTY AVR_MCU_FREQ BRIEF_DOCS "DEBUG" FULL_DOCS "DEBUG" )

  add_executable ( ${AVR_TARGET} ${AVR_SOURCES} )

  set_target_properties ( ${AVR_TARGET} PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_MCU_FREQ}UL ${AVR_CFLAGS}"
    LINK_FLAGS    "-mmcu=${AVR_MCU} ${AVR_LFLAGS}"
  )

  target_include_directories ( ${AVR_TARGET} PRIVATE "/usr/include/simavr" )

  set_property ( TARGET ${AVR_TARGET} PROPERTY AVR_MCU      ${AVR_MCU}      )
  set_property ( TARGET ${AVR_TARGET} PROPERTY AVR_MCU_FREQ ${AVR_MCU_FREQ} )
endfunction ( avr_add_executable )

function ( avr_add_library AVR_TARGET )
  cmake_parse_arguments ( PARSE_ARGV 1 AVR "" "" "PROPERTIES" )
  set ( AVR_SOURCES ${AVR_UNPARSED_ARGUMENTS} )
  cmake_parse_arguments ( AVR "" "MCU;MCU_FREQ" "" ${AVR_PROPERTIES} )

  define_property ( TARGET PROPERTY AVR_MCU      BRIEF_DOCS "DEBUG" FULL_DOCS "DEBUG" )
  define_property ( TARGET PROPERTY AVR_MCU_FREQ BRIEF_DOCS "DEBUG" FULL_DOCS "DEBUG" )

  add_library ( ${AVR_TARGET} STATIC ${AVR_SOURCES} )

  set_target_properties ( ${AVR_TARGET} PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_MCU_FREQ}UL ${AVR_CFLAGS}"
    LINK_FLAGS    "-mmcu=${AVR_MCU} ${AVR_LFLAGS}"
  )

  target_include_directories ( ${AVR_TARGET} PRIVATE "/usr/include/simavr" )

  set_property ( TARGET ${AVR_TARGET} PROPERTY AVR_MCU      ${AVR_MCU}      )
  set_property ( TARGET ${AVR_TARGET} PROPERTY AVR_MCU_FREQ ${AVR_MCU_FREQ} )
endfunction ( avr_add_library )

function ( avr_target_include_directories AVR_TARGET )
  target_include_directories ( ${AVR_TARGET} PRIVATE ${ARGN} )
endfunction ( avr_target_include_directories )

function ( avr_target_link_libraries AVR_TARGET )
  get_property ( AVR_MCU      TARGET ${AVR_TARGET} PROPERTY AVR_MCU      )
  get_property ( AVR_MCU_FREQ TARGET ${AVR_TARGET} PROPERTY AVR_MCU_FREQ )

  foreach ( AVR_LIBRARY IN ITEMS ${ARGN} )
    get_property ( AVR_MCU_TEMP      TARGET ${AVR_LIBRARY} PROPERTY AVR_MCU      )
    get_property ( AVR_MCU_FREQ_TEMP TARGET ${AVR_LIBRARY} PROPERTY AVR_MCU_FREQ )
    if ( NOT ${AVR_MCU}      STREQUAL ${AVR_MCU_TEMP}     OR
         NOT ${AVR_MCU_FREQ}    EQUAL ${AVR_MCU_FREQ_TEMP} )
      message ( FATAL_ERROR "MCU and/or Frequency mismatch" )
    endif (  )
  endforeach (  )

  target_link_libraries ( ${AVR_TARGET} PRIVATE ${ARGN} )
endfunction ( avr_target_link_libraries )

function ( avr_hexeep AVR_TARGET )
  add_custom_command ( OUTPUT ${AVR_TARGET}.hex
    COMMAND ${AVR_OBJCOPY}
      -j .text
      -j .data
      -O ihex ${AVR_TARGET} ${AVR_TAGRET}.hex
    DEPENDS ${AVR_TARGET}
  )
  
  add_custom_command ( OUTPUT ${AVR_TARGET}.eep
    COMMAND ${AVR_OBJCOPY}
      -j .eeprom
      --set-section=.eeprom=alloc,load
      --change-section-lma .eeprom=0
      --no-change-warnings
      -O ihex ${AVR_TARGET} ${AVR_TARGET}.eep
    DEPENDS ${AVR_TARGET}
  )
endfunction ( avr_hex )

function ( avr_upload AVR_TARGET )
  cmake_parse_arguments ( PARSE_ARGV 1 AVR "" "" "OPTIONS" )
  cmake_parse_arguments ( AVR "" "PROGRAMMER;PROGRAMMER_PORT;PROGRAMMER_RATE" "" ${AVR_OPTIONS} )

  avr_hexeep ( ${AVR_TARGET} )

  add_custom_target ( ${AVR_TARGET}_upload
    COMMAND ${AVR_AVRDUDE}
      -p ${AVR_MCU}
      -c ${AVR_PROGRAMMER}
      -b ${AVR_PROGRAMMER_RATE}
      -P ${AVR_PROGRAMMER_PORT}
      -U flash:w:${AVR_TARGET}.hex
      -U eeprom:w:${AVR_TARGET}.eep
    DEPENDS ${AVR_TARGET}.hex ${AVR_TARGET}.eep
  )
endfunction ( avr_upload )

function ( avr_disasm AVR_TARGET )
  add_custom_target ( ${AVR_TARGET}_disasm ALL
    COMMAND ${AVR_OBJDUMP} -j .text -j .data -j .bss -j .eeprom -j .mmcu -d ${AVR_TARGET} > ${AVR_TARGET}.asm
    BYPRODUCTS ${AVR_TARGET}.asm
    DEPENDS ${AVR_TARGET}
  )
endfunction ( avr_disasm )

function ( avr_size AVR_TARGET )
  get_property ( AVR_MCU TARGET ${AVR_TARGET} PROPERTY AVR_MCU )
  add_custom_target ( ${AVR_TARGET}_size ALL
    COMMAND ${AVR_SIZE} -C --mcu=${AVR_MCU} ${AVR_TARGET}
    DEPENDS ${AVR_TARGET}
  )
endfunction ( avr_size )

function ( avr_simulate AVR_TARGET )
  get_property ( AVR_MCU      TARGET ${AVR_TARGET} PROPERTY AVR_MCU      )
  get_property ( AVR_MCU_FREQ TARGET ${AVR_TARGET} PROPERTY AVR_MCU_FREQ )

  add_custom_target ( ${AVR_TARGET}_simavr ALL
    COMMAND ${AVR_SIMAVR} -v -v -v -m ${AVR_MCU} -f ${AVR_MCU_FREQ} -t ${AVR_TARGET}
    DEPENDS ${AVR_TARGET}
  )
endfunction ( avr_simulate )
