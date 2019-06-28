project(algorithms)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG)

set(BUILD_FLAGS "-O3 -ggdb -fsanitize=address -pedantic -Wall -Wextra -Wno-vla")
set(CMAKE_C_FLAGS ${BUILD_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${BUILD_FLAGS})
set(CMAKE_C_FLAGS_RELEASE ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${BUILD_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${BUILD_FLAGS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(tools)

add_subdirectory(tools)
add_subdirectory(leetcode)
add_subdirectory(hackerrank)
