include_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(./ DIR_SOURCES)

add_executable(demo4 ${DIR_SOURCES})

target_link_libraries(demo4 mylib)