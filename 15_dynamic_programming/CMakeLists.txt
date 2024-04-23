cmake_minimum_required(VERSION 3.10)
project(15_dynamic_programming)

# Main executable
add_executable(15_dynamic_programming_main cpp/main.cpp)
target_link_libraries(15_dynamic_programming_main PRIVATE common)
target_include_directories(15_dynamic_programming_main PRIVATE ../common)

# Exercise executable
add_executable(15_dynamic_programming_exercise exercises/exercise.cpp)
target_link_libraries(15_dynamic_programming_exercise PRIVATE common)
target_include_directories(15_dynamic_programming_exercise PRIVATE ../common)
