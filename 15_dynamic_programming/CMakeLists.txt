cmake_minimum_required(VERSION 3.10)
project(15_dynamic_programming)

# Main executable
add_executable(15_dynamic_programming_main cpp/main.cpp)
target_link_libraries(15_dynamic_programming_main PRIVATE common)
target_include_directories(15_dynamic_programming_main PRIVATE ../common)

# Exercises executable
add_executable(15_dynamic_programming_exercises cpp/exercises.cpp)
target_link_libraries(15_dynamic_programming_exercises PRIVATE common)
target_include_directories(15_dynamic_programming_exercises PRIVATE ../common)