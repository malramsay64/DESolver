cmake_minimum_required(VERSION 3.3)
project(shear)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(cblas)

set(SOURCE_FILES
    lib/differentiate.cpp
    lib/differentiate.h
    lib/integrator.cpp
    lib/integrator.h
    lib/main.cpp
    lib/noise.cpp
    lib/noise.h)

add_executable(shear ${SOURCE_FILES})