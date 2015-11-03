cmake_minimum_required(VERSION 3.3)
project(shear)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)

link_libraries(cblas gtest pthread)

set(SOURCE_FILES
        lib/differentiate.cpp
        lib/differentiate.h
        lib/integrator.cpp
        lib/integrator.h
        lib/noise.cpp
        lib/noise.h lib/functions.cpp lib/functions.h)

add_executable(shear lib/main.cpp ${SOURCE_FILES})

add_executable(runBasicTests tests/basictest.cpp ${SOURCE_FILES})

add_executable(runComplexTests tests/complextest.cpp ${SOURCE_FILES})