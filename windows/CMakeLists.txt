## DATE: 25th Feb 2017
## COPYRIGHT: STEALTHY LABS LLC

cmake_minimum_required(VERSION 3.0)
#enable_testing()
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)
if (WIN32)
    if (MSVC)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(COMPILER_FLAGS "/MDd")
        else (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(COMPILER_FLAGS "/MD")
        endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS}")
    endif (MSVC)
else (WIN32)
    message(FATAL_ERROR "Currently only supported on Windows")
endif (WIN32)
# examples of inline assembly in both 2 and 64 bit mode
add_executable(helloworld helloworld.c)
