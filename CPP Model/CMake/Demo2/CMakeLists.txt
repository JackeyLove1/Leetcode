cmake_minimum_required(VERSION 3.16)

project(Demo2)

aux_source_directory(. DIR_SRCS)

add_executable(Demo2 ${DIR_SRCS})