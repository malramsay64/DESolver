cmake_minimum_required(VERSION 2.8)
project(shear)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "NO build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        lib/noise.cpp
        lib/noise.h
        lib/functions.cpp
        lib/functions.h
        lib/input.cpp
        lib/input.h
        lib/Integrator.cpp
        lib/Integrator.h
        lib/Equation.cpp
        lib/Equation.h
        lib/Search.cpp
        lib/Search.h
        )

# Include stats
include_directories($ENV{HOME}/.local/include)
link_directories($ENV{HOME}/.local/lib)

link_libraries(stats)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(tests/lib/gtest-1.7.0)
    include_directories(tests/lib/gtest-1.7.0/include)

    link_libraries(gtest pthread)
    add_executable(runTests tests/runTests.cpp ${SOURCE_FILES})
endif()

add_executable(shear lib/main.cpp ${SOURCE_FILES})

SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)
install(TARGETS shear
        CONFIGURATIONS Release
        DESTINATION bin
        )


