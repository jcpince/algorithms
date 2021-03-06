project(algorithms)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG)

set(BUILD_FLAGS "-O0 -ggdb -fsanitize=address -pedantic -Wall -Wextra -Wno-vla -Wno-vla-extension")
set(CMAKE_C_FLAGS ${BUILD_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${BUILD_FLAGS})
set(CMAKE_C_FLAGS_RELEASE ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${BUILD_FLAGS})
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeRust/cmake")

enable_language(Rust)
include(CMakeCargo)

cargo_build(NAME rslib)

macro(add_problem problem_name)
    message("Adding problem: ${problem_name}")
    add_executable(${problem_name} ${problem_name}.cpp main.cpp)
    target_link_libraries(${problem_name} unittests)
    #set_property(TARGET ${problem_name} PROPERTY CXX_STANDARD 20)
endmacro()

include_directories(tools)
include_directories(algos)

link_directories(${CMAKE_BINARY_DIR}/x86_64-unknown-linux-gnu/debug)

add_subdirectory(tools)
add_subdirectory(leetcode)
add_subdirectory(hackerrank)
add_subdirectory(algos)
add_subdirectory(topcoder)
