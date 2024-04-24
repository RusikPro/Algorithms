cmake_minimum_required(VERSION 3.10)
project(CommonLib)

# Collect all source files in the common directory
file(GLOB COMMON_SOURCES "*.cpp")

# Create a static library named 'common'
add_library(common STATIC ${COMMON_SOURCES})

# Specify where the common headers are
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
