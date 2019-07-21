set(targetName testBuble)
add_executable(${targetName} testBuble.cpp)
link_directories(${INCLUDE_DIR})
target_link_libraries(${targetName} BaseAlgo)

add_executable(testQuick testQuickSort.cpp)
link_directories(${INCLUDE_DIR})
target_link_libraries(testQuick BaseAlgo)
