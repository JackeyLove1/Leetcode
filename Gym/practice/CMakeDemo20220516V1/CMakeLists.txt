cmake_minimum_required(VERSION 3.16)

project(demo8)
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

include_directories(${PROJECT_SOURCE_DIR}/include)
# set(SOURCES ${PROJECT_SOURCE_DIR}/src/mymath.cpp ${PROJECT_SOURCE_DIR}/src/main.cpp)
file(GLOB SOURCES "src/*.cpp")
message(STATUS "file: ${SOURCES}")
add_library(hello_lib STATIC ${PROJECT_SOURCE_DIR}/src/hello.cpp)
target_link_directories(hello_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_executable(demo8 ${SOURCES})
target_link_libraries(demo8 PUBLIC hello_lib)
# target_link_directories(demo8 PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "ARCHIVE_DIR: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
