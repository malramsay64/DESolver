cmake_minimum_required(VERSION 2.8)
project(shear)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicTests basictest.cpp)

target_link_libraries(runBasicTest gtest gtest_main)