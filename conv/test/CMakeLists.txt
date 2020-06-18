set(targetName testConv)
set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_PATH})
add_executable(${targetName} testConv.cpp)
link_directories(${INCLUDE_DIR})
target_link_libraries(${targetName} conv)

