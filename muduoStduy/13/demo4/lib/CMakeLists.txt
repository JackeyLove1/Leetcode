aux_source_directory(./ DIR_SOURCES)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(mylib STATIC ${DIR_SOURCES})