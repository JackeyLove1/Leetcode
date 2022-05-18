project(demo9)

message(STATUS "sub2_DIR: ${CMAKE_CURRENT_LIST_DIR}")
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
add_library(world ${CMAKE_CURRENT_LIST_DIR}/src/world.cpp)
