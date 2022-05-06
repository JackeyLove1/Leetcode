cmake_minimum_required(VERSION 3.16)
project(TinyLog)

set(CMAKE_CXX_FLAGS
        -O2
        -g
        -Wall
        -Wextra
        -Werror
        -std=c++17
        -pthread
        )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/util
)

LINK_LIBRARIES(
        ${PROJECT_BINARY_DIR}/libs
)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# cmake info display
message(STATUS "CMAKE_CXX_FLAGS = " "${CMAKE_CXX_FLAGS}")
message(STATUS "PROJECT_BINARY_DIRECTORY=" "${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIRECTORY=" "${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR=" "${CMAKE_BINARY_DIR}")
message(STATUS "GTEST_SOURCE_DIR=" "${gtest_SOURCE_DIR}")
message(STATUS "LIBRAY_OUTPUT_DIR=" "${PROJECT_BINARY_DIR}/libs")