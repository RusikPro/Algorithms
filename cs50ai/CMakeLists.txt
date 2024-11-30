cmake_minimum_required(VERSION 3.10)
project(cs50ai)

# Main executable
add_executable(cs50ai_main cpp/main.cpp)
target_link_libraries(cs50ai_main PRIVATE common)
target_include_directories(cs50ai_main PRIVATE ../common)

# Exercises executable
add_executable(cs50ai_exercises cpp/exercises.cpp)
target_link_libraries(cs50ai_exercises PRIVATE common)
target_include_directories(cs50ai_exercises PRIVATE ../common)
