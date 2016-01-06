cmake_minimum_required(VERSION 3.3)
project(shear)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests runTests.cpp)

target_link_libraries(runTests gtest gtest_main)
