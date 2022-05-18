project(demo9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
add_library(hello ${CMAKE_CURRENT_LIST_DIR}/src/hello.cpp)
# target_link_directories(${CMAKE_CURRENT_LIST_DIR}/include)