cmake_minimum_required(VERSION 3.10)
project(test_chapter2)

# Main executable
add_executable(test_chapter2_main cpp/main.cpp)
target_link_libraries(test_chapter2_main PRIVATE common)
target_include_directories(test_chapter2_main PRIVATE ../common)

# Exercise executable
add_executable(test_chapter2_exercise exercises/exercise.cpp)
target_link_libraries(test_chapter2_exercise PRIVATE common)
target_include_directories(test_chapter2_exercise PRIVATE ../common)

