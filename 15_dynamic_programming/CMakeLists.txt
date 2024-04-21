cmake_minimum_required(VERSION 3.10)
project(15_dynamic_programming)

add_executable(main cpp/main.cpp)
target_link_libraries(main PRIVATE common)
target_include_directories(main PRIVATE ../common)

add_executable(exercise exercises/exercise.cpp)
target_link_libraries(exercise PRIVATE common)
target_include_directories(exercise PRIVATE ../common)