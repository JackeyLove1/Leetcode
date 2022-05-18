cmake_minimum_required(VERSION 3.0)

project(demo9)

set(CXX_FLAGS -O2 -g -Wall -Wextra -Werror -std=c++20 -pthread)

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

add_subdirectory(sublib)
add_subdirectory(sublib1)
add_subdirectory(sublib2)

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR} *.cpp)
message(STATUS "srcs: ${srcs}")