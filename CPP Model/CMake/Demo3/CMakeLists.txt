cmake_minimum_required(VERSION 3.16)

project(Demo3)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. DIR_SRCS)

add_subdirectory(math)
add_executable(Demo3 main.cpp)
target_link_libraries(Demo3 MathFunctions)