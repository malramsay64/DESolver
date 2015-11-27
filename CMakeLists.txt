cmake_minimum_required(VERSION 2.8)
project(shear)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tests/lib/gtest-1.7.0)
#find_library(gtest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
include_directories(tests/lib/gtest-1.7.0/include)

link_libraries(gtest pthread)

set(SOURCE_FILES
        lib/differentiate.cpp
        lib/differentiate.h
        lib/integrator.cpp
        lib/integrator.h
        lib/noise.cpp
        lib/noise.h
        lib/functions.cpp
        lib/functions.h
        lib/output.cpp
        lib/output.h
        lib/stability.cpp
        lib/stability.h
        lib/input.cpp
        lib/input.h
        lib/search.cpp
        lib/search.h lib/stochastic_search.cpp lib/stochastic_search.h)

add_executable(shear lib/main.cpp ${SOURCE_FILES})
add_executable(runBasicTests tests/basictest.cpp ${SOURCE_FILES})
add_executable(runComplexTests tests/complextest.cpp ${SOURCE_FILES})

