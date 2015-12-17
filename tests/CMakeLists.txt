cmake_minimum_required(VERSION 3.3)
project(shear)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicTests runTests.cpp)
add_executable(runComplexTests complextest.cpp)

target_link_libraries(runBasicTests gtest gtest_main)
target_link_libraries(runComplexTests gtest gtest_main)