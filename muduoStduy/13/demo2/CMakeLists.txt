cmake_minimum_required(VERSION 3.10)

project(demo2)

aux_source_directory(./ DIRCT_SOURCE)

add_executable(demo2 ${DIRCT_SOURCE})