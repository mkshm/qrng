
add_executable ( tst-freq     tst-freq.c )
add_executable ( tst-monte-3d tst-monte-3d.c )

target_include_directories ( tst-freq     PRIVATE ${CMAKE_SOURCE_DIR}/tests )
target_include_directories ( tst-monte-3d PRIVATE ${CMAKE_SOURCE_DIR}/tests )

target_link_libraries ( tst-freq     PRIVATE -lm )
target_link_libraries ( tst-monte-3d PRIVATE -lm )
