cmake_minimum_required(VERSION 3.16)

project(demo3)

add_subdirectory(./mylib)

aux_source_directory(./ DIR_SOURCES)

add_executable(demo3 ${DIR_SOURCES})

target_link_libraries(demo3 mylib)