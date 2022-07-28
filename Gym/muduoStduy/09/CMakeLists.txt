cmake_minimum_required(VERSION 3.16)
project(Study)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS -g -Wall)


add_executable(Study main.cpp Thread.h Thread.cpp)
target_link_libraries(Study pthread)
