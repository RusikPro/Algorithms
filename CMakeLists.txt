cmake_minimum_required(VERSION 3.10)
project(Algorithms)

# Include FetchContent module
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# Make Google Test available
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(common)
add_subdirectory(15_dynamic_programming)
add_subdirectory(22_elementary_graph_algorithms)
add_subdirectory(try_outs)
add_subdirectory(leetcode)
add_subdirectory(fintech)
