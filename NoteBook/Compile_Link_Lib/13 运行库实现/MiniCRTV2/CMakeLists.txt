cmake_minimum_required(VERSION 3.10)

project(MiniCRT LANGUAGES C CXX)

if(${MiniCRT_SOURCE_DIR} STREQUAL ${MiniCRT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# Set C gnu11
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(MiniCRT_SOURCE_CODE_DIR ${MiniCRT_SOURCE_DIR}/src)
add_subdirectory(${MiniCRT_SOURCE_CODE_DIR})


