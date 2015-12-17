cmake_minimum_required(VERSION 2.8)
project(shear)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "NO build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tests/lib/gtest-1.7.0)
#find_library(gtest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
include_directories(tests/lib/gtest-1.7.0/include)

link_libraries(gtest pthread)

set(SOURCE_FILES
        lib/noise.cpp
        lib/noise.h
        lib/functions.cpp
        lib/functions.h
        lib/input.cpp
        lib/input.h
        lib/Equation.cpp
        lib/Equation.h
        lib/Integrator.cpp
        lib/Integrator.h)

add_executable(shear lib/main.cpp ${SOURCE_FILES})
add_executable(runTests tests/runTests.cpp ${SOURCE_FILES})

