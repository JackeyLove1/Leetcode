cmake_minimum_required(VERSION 3.16)

project(MathFunctions)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. DIR_LIB_SRCS)

add_library(MathFunctions ${DIR_LIB_SRCS})