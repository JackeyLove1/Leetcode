cmake_minimum_required(VERSION 3.16)
project(NanoLog)

set(CMAKE_CXX_STANDARD 20)
aux_source_directory(./ SOURCE_LIST)
add_subdirectory(./googletest)
set(CXX_FLAGS
        -O2
        # -O0
        -g
        -Wall
        -Wextra
        -Werror
        -std=c++20
        -pthread
        )
set(LIBRARIES
        gtest
        pthread
        )
add_executable(main ${SOURCE_LIST})
target_link_libraries(main ${LIBRARIES})
