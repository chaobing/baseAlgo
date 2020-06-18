include_directories(${INCLUDE_DIR})
aux_source_directory(. DIR_SOLUTION_SRCS)
add_library(conv ${DIR_SOLUTION_SRCS})
