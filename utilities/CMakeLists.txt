
add_executable ( serial_listen ${CMAKE_SOURCE_DIR}/utilities/serial_listen.c )

target_include_directories ( serial_listen PRIVATE ${CMAKE_SOURCE_DIR}/utilities/include )
