PROJECT(TinyLog)

#madd_executable(hello hello.cpp)

function(unit_test test_file)
    set(SRCS)
    message("UNIT_TEST")
    if (${ARGC} EQUAL 1)
        message(FATAL_ERROR "Build unit test error for the src list empty")
    else ()
        set(INDEX 1)
        while (INDEX LESS ${ARGC})
            list(APPEND SRCS ${ARGV${INDEX}})
            math(EXPR INDEX "${INDEX}+1")
            message(STATUS "SRCS: " ${SRCS})
        endwhile ()
        add_executable(${test_file} ${SRCS})
        target_link_libraries(${test_file} gtest TinyLog)
    endif ()
endfunction()

unit_test(HelloWord hello.cpp)
unit_test(HelloTest hello_test.cpp)