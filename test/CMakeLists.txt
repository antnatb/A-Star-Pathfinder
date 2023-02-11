cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest-main)
set(gtest_SOURCE_DIR, ./lib/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES GridTest.cpp CellTest.cpp runAllTests.cpp)
add_executable(runGridTest ${TEST_SOURCE_FILES})
target_link_libraries(runGridTest gtest gtest_main core)


