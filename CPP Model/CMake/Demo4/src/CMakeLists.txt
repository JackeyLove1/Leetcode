PROJECT(TinyLog)

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR} *.cpp)

add_library(TinyLog STATIC ${srcs})
set_target_properties(TinyLog PROPERTIES OUTPUT_NAME "TinyLog")
set_target_properties(TinyLog PROPERTIES CLEAN_DIRECT_OUTPUT 1)